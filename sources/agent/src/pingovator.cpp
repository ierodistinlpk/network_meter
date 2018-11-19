/*****************************************************/
/*****************************************************
 *   Pingovator.cpp
 *   Copyright (C) 2009 by IERO  aka Michael Kartashov *
 *   iero@lna.org.ru   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
*******************************************************
part of code is from UNIX ping program
http://www.ping127001.com/pingpage
*******************************************************/


#include "datatypes.h"
#include "pingovator.h"
#include "NetEvent.h"
#include "NetResult.h"
#include "Cycle.h"
#include "Agent.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string>
#include <list>
#include <map>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
unsigned short Crc16 ( unsigned char *pcBlock, unsigned short len );
u_short in_cksum ( const u_short *addr, register int len, u_short csum );
unsigned int tv_sub ( timestamp_t out, timestamp_t in ); //возвращает время отклика в МИКРОСЕКУНДАХ
// Constructors/Destructors
//
/* конструктор*/
Pingovator::Pingovator ( Agent* cmdr ) : m_time_to_die ( 0 )
{
  m_socket= socket ( PF_INET, SOCK_RAW,IPPROTO_ICMP );
  cout<<"create raw sock: "<<strerror ( errno ) <<endl;
//тут всякие сокадр_ин и т.п. добавить
  comandor=cmdr;
  pthread_mutex_init ( &ProbeMutex,NULL );
  m_Query.clear();
  if ( ( pthread_create ( &m_f_thread, NULL, & ( Pingovator::FstThread ),this ) ) !=0 ) //в этом треде крутится посылка
    cout<<"PPC1"<<endl;
  if ( ( pthread_create ( &m_s_thread, NULL, & ( Pingovator::SecThread ),this ) ) !=0 ) //в этом треде крутится принялка
    cout<<"PPC2"<<endl;

}

/*деструктор*/
Pingovator::~Pingovator ( )
{
  m_time_to_die=1;
  pthread_join ( m_f_thread,NULL );
  pthread_join ( m_s_thread,NULL );
  m_Query.clear();
  pthread_mutex_destroy ( &ProbeMutex );
  close ( m_socket );
}
/* * добавляет цикл в очередь. */
void Pingovator::AddCycle ( Cycle &cycle )
{
  pthread_mutex_lock ( &ProbeMutex ); //чтобы не подрались кто в пинговатор пишет
  m_Query.push_back ( cycle );
  pthread_mutex_unlock ( &ProbeMutex ); //отпускаем очередь пингалки
}


/** *второй поток. служит для приема всего попадающего на сокет. */
void Pingovator::initReadSocket ( )
{
  //сюда пихаем читалку сырого сокета
  int size;
  unsigned short chksumma;
  raw_body_t * icmpbody;// = (raw_body_t *)(m_SBuf+sizeof(icmphdr));
  long long idprobe;
  unsigned long cuclenum;
  timestamp_t timestamp;
  struct sockaddr_in from; //принимает адрес сообщения
  struct sockaddr * fromptr= ( sockaddr* ) ( &from ); //принимает адрес сообщения
  socklen_t fromlen=sizeof ( from );
  iphdr * iph= ( iphdr* ) m_RBuf;
  map<map_key,NetResult*>::iterator map_it;
  while ( ! m_time_to_die )
  {
    if ( ( size=recvfrom ( m_socket,m_RBuf,sizeof ( m_RBuf ),0 , fromptr, &fromlen ) ) <0 )
    {
      cout<<"raw recv: "<<strerror ( errno ) <<endl;
    }
    // обработчик принятой гадости
    else
    {
      icmphdr * icmph= ( icmphdr* ) ( m_RBuf+4*iph->ihl );
      switch ( icmph->type )
      {
        case ICMP_ECHOREPLY:
          if ( ntohs ( icmph->un.echo.id ) !=getpid() )
            break;
          gettimeofday ( &timestamp,NULL );
          icmpbody = ( raw_body_t * ) ( m_RBuf+4*iph->ihl +sizeof ( icmphdr ) );
          idprobe=icmpbody->idprobe;
          cuclenum=ntohl ( icmpbody->number );
          //искать постстрингу с таким ИД и номером
          map_it=m_ResMap.find ( map_key ( idprobe, cuclenum ) );
          //считать разность в микросекундах
          if ( map_it==m_ResMap.end() )
            break;
          map_it->second->AddResult ( tv_sub ( timestamp,map_it->second->getTime() ),ntohs ( icmph->un.echo.sequence ) );
          if ( map_it->second->getCurCount() ==0 )
          {
            //вытаскиваем из мапы как готовую и отдаем агенту на посылку.
            comandor->AddResult ( map_it->second );
            m_ResMap.erase ( map_it );
          }
    //      cout<<"PING:"<<idprobe<<" "<<cuclenum<<" "<<ntohs ( icmph->un.echo.sequence ) <<endl;
          break;
          //    case ICMP_ECHO
        case ICMP_DEST_UNREACH:
        case ICMP_SOURCE_QUENCH:
        case ICMP_TIME_EXCEEDED:
        case ICMP_PARAMETERPROB:
        {
          iphdr * in_iph = ( iphdr* ) ( ( ( char* ) icmph ) +sizeof ( icmphdr ) );
          icmphdr * in_icmph= ( icmphdr* ) ( ( ( char* ) in_iph ) + ( 4*in_iph->ihl ) );
          for ( unsigned i=0;i<36;i++ )
          {
            icmpbody= ( raw_body_t * ) ( ( ( char* ) in_icmph ) +i ); //постепенно смещаемся по буферу в возвращенном фрагменте.
            if ( strncmp ( icmpbody->msg_pref,"AOR_",4 ) ) //ищем сигнальный префикс
              continue;
            //нашли префикс
            chksumma=Crc16 ( ( unsigned char* ) icmpbody,24 );
            if ( icmpbody->chksumma!=chksumma )            //проверяем данные чексумой.
              continue;
            idprobe=icmpbody->idprobe;
            cuclenum=ntohl ( icmpbody->number );
            //создавать евент
              NetEvent * event = new NetEvent ( iph->saddr,idprobe,cuclenum,EV_T_ICMP, icmph->type );
              comandor->AddResult ( event );
            //писать в соответствующий результат -1
          //  cout<<"ICMP recved probe "<<idprobe<<" "<<cuclenum<<" "<<ntohs ( icmpbody->ping_num ) <<endl;
            map_it=m_ResMap.find ( map_key ( idprobe,cuclenum ) );
            if ( map_it==m_ResMap.end() )
              break;
            map_it->second->AddResult ( -1,ntohs ( icmpbody->ping_num ) );
            if ( map_it->second->getCurCount() ==0 )
            {
              //вытаскиваем из мапы как готовую и отдаем агенту на посылку.
              comandor->AddResult ( map_it->second );
              m_ResMap.erase ( map_it );
            }
            break;
          }
        }
        break;
      }
    }
  }
}


/* выполняет первый в очереди цикл и удаляет выполненый цикл из очереди */
void Pingovator::ExecCycle ( )
{
  idprobe_t loc_id;
  unsigned long loc_num;
  unsigned short loc_count;
  while ( ! m_time_to_die )
  {
    if ( m_Query.empty() )
    {
      usleep ( 1000 );
      continue;
    }
    loc_id=m_Query.front().getIdProbe();
    loc_num=m_Query.front().getNumber();
    loc_count=m_Query.front().getCount();
    map_key key ( loc_id,loc_num );
    NetResult * result = new NetResult ( loc_id,loc_num, loc_count );
    m_ResMap[key]= result;
//отрабатываем цикл
// /**********************************************************************************/
    for ( short j =0;j<loc_count;j++ ) //начинаем работать с одним пакетом.
    {
      memset ( m_SBuf,0,loc_count );
      //забиваем буфер полезной штукой
//утт нужна сокадр_ин
      struct sockaddr whereto;/* Who to ping */
      struct sockaddr_in * to= ( struct sockaddr_in * ) ( &whereto );
      memset ( ( char * ) &whereto,0, sizeof ( struct sockaddr ) );
      to->sin_family = AF_INET;
      to->sin_addr.s_addr = m_Query.front().getTarget();
      //ICMP-header
      raw_body_t * icmpbody = ( raw_body_t * ) ( m_SBuf+sizeof ( icmphdr ) );
      struct icmphdr * icmph= ( struct icmphdr * ) ( m_SBuf );
      icmph->type=ICMP_ECHO; //ICMP заголовок пинга
      icmph->code=0;
      icmph->checksum=0;
      icmph->un.echo.id=htons ( getpid() );
      icmph->un.echo.sequence=htons ( j );
      timestamp_t curtime;
      gettimeofday ( &curtime, NULL );
      //пошло тело пинга.
      unsigned char * iter=m_SBuf;
      short k=0;
      strncpy ( icmpbody->msg_pref,"AOR_IERO",4 );
      icmpbody->idprobe=loc_id;
      icmpbody->time=curtime;
      icmpbody->number=htonl ( loc_num );
      icmpbody->ping_num=htons ( j );
      icmpbody->chksumma=Crc16 ( ( unsigned char* ) icmpbody,24 );
      while ( iter<m_SBuf+m_Query.front().getSize() )
      {
        memcpy ( m_SBuf+PING_HDR_SIZE+k*sizeof ( raw_body_t ),icmpbody,sizeof ( raw_body_t ) );
        k++;
        iter+=PING_DATA_SIZE;
      }
      icmph->checksum= in_cksum ( ( unsigned short* ) m_SBuf,m_Query.front().getSize(), 0 );
      if ( sendto ( m_socket, m_SBuf, m_Query.front().getSize(), 0, &whereto, sizeof ( struct sockaddr ) ) <m_Query.front().getSize() )
      {
        NetEvent * event = new NetEvent ( m_Query.front().getTarget(),loc_id,m_Query.front().getNumber(),EV_T_ERRNO,errno );
        // добавляем в очередь
        comandor->AddResult ( event );
        //заполняем соответствующую ячейку в результатах
        result->AddResult ( -1,j );
      }
    }
    timestamp_t timestamp;
    gettimeofday ( &timestamp,NULL );
    for ( map<map_key,NetResult*>::iterator map_it=m_ResMap.begin();map_it!=m_ResMap.end();map_it++ )   //очищаем устаревших
    {
      if ((( timestamp.tv_sec - map_it->second->getTime().tv_sec) >=MAX_RES_TIMEOUT  ))
      {
        cout<<"difference:"<<timestamp.tv_sec - map_it->second->getTime().tv_sec<<endl;
        cout<<"    extracting   "<<endl;
        //вытаскиваем из мапы как готовую и отдаем агенту на посылку.
        comandor->AddResult ( map_it->second );
        m_ResMap.erase ( map_it );
      }
    }
    pthread_mutex_lock ( &ProbeMutex );
    m_Query.pop_front(); //секурно удаляем отработаный цикл из очереди.
    pthread_mutex_unlock ( &ProbeMutex );
  }
}

void * Pingovator::FstThread ( void * pthis )
{
  Pingovator * curpingovator = ( Pingovator* ) pthis;
  curpingovator->ExecCycle();
  return NULL;
}
/* * поток выполняющий read на сокете.
передает результат в буфер агента */
void * Pingovator::SecThread ( void * pthis )
{
  Pingovator * curpingovator = ( Pingovator* ) pthis;
  curpingovator->initReadSocket();
  return NULL;
}

/*
 *			I N _ C K S U M
 *
 * Checksum routine for Internet Protocol family headers (C Version)
 *
 */
u_short
in_cksum ( const u_short *addr, register int len, u_short csum )
{
  register int nleft = len;
  const u_short *w = addr;
  register u_short answer;
  register int sum = csum;

  /*
  *  Our algorithm is simple, using a 32 bit accumulator (sum),
  *  we add sequential 16 bit words to it, and at the end, fold
  *  back all the carry bits from the top 16 bits into the lower
  *  16 bits.
        */
  while ( nleft > 1 )
  {
    sum += *w++;
    nleft -= 2;
  }

  /* mop up an odd byte, if necessary */
  if ( nleft == 1 )
    sum += htons ( * ( u_char * ) w << 8 );

  /*
  * add back carry outs from top 16 bits to low 16 bits
        */
  sum = ( sum >> 16 ) + ( sum & 0xffff );	/* add hi 16 to low 16 */
  sum += ( sum >> 16 );			/* add carry */
  answer = ~sum;				/* truncate to 16 bits */
  return ( answer );
}


unsigned int   tv_sub ( timestamp_t out, timestamp_t in )
{
  if ( ( out.tv_usec -= in.tv_usec ) < 0 )  	/* out -= in */
  {
    --out.tv_sec;
    out.tv_usec += 1000000;
  }
  out.tv_sec -= in.tv_sec;
  return out.tv_sec*1000000+out.tv_usec;
}
