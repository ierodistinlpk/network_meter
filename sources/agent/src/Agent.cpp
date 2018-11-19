/************************************************************************
                        Agent.h.cpp - Copyright iero

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/share/apps/umbrello/headings/heading.cpp

-->Code Generators searches for heading files based on the file extension
   i.e. it will look for a file name ending in ".h" to include in C++ header
   files, and for a file name ending in ".java" to include in all generated
   java code.
   If you name the file "heading.<extension>", Code Generator will always
   choose this file even if there are other files with the same extension in the
   directory. If you name the file something else, it must be the only one with that
   extension in the directory to guarantee that Code Generator will choose it.

you can use variables in your heading files which are replaced at generation
time. possible variables are : author, date, time, filename and filepath.
just write %variable_name%

This file was generated on Пнд Мар 23 2009 at 19:52:10
The original location of this file is /media/s2/univer/diplomko/agent_nix/Agent.cpp
**************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "Agent.h"
#include "pingovator.h"
#include "datatypes.h"
#include "md5.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <vector>
#include <list>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

Agent::Agent ( ) :m_time_to_die ( 0 ), m_Port ( 1234 ),m_Soket ( -1 ),  m_next_result ( 0 ), m_cur_post ( 0 ),  m_SessionId ( 0 )
{
  m_PostList.clear();
  m_ProbeList.clear();
  pthread_mutex_init ( &send_mut,NULL ); 
  pthread_mutex_init ( &m_query_mutex,NULL ); 
  last_request_time.tv_sec=0;
  last_request_time.tv_usec=0;
  last_comm_time.tv_sec=0;
  last_comm_time.tv_usec=0;
  m_comm_seq=0;
  m_pinger = new Pingovator ( this );
  m_Address="localhost";
  m_Name="name";
  m_SrvName="srvname";
  m_secret=":) :)";
  memset ( &m_HRBuf,0, sizeof ( m_HRBuf ) );
  memset ( &m_RBuf,0, DBUF_SIZE );
  memset ( &m_HSBuf,0, sizeof ( m_HSBuf ) );
  memset ( &m_SBuf,0, DBUF_SIZE );
  //указатели на структуры на буфер
  pintro= ( intro_s* ) m_RBuf;
  psesstart= ( sesstart_s* ) m_RBuf;
  pdisconnect= ( disconnect_s* ) m_RBuf;
  pgetclstate= ( getclstate_s* ) m_RBuf;
  psetprobe= ( setprobe_s* ) m_RBuf;
  pdataack= ( dataack_s* ) m_RBuf;
  plogin = ( login_s * ) m_SBuf;
  pclientstate = ( clientstate_s * ) m_SBuf ;
  pproberesult= ( proberesult_s * ) m_SBuf;
  peventlog = ( eventlog_s * )  m_SBuf;
  pclientdisconnect = ( cldisconnect_s * ) m_SBuf;

}

Agent::~Agent ( )
{
  for ( list<Probe*>::iterator iter=m_ProbeList.begin();iter!=m_ProbeList.end(); iter++ )
    delete *iter;
  delete m_pinger;
  for ( list<Post*>::iterator iter=m_PostList.begin();iter!=m_PostList.end(); iter++ )
    delete *iter;
  m_PostList.clear();
  m_ProbeList.clear();
  pthread_mutex_destroy ( &send_mut );
  pthread_mutex_destroy ( &m_query_mutex );
}
/* запускает всю работу агента.
 * по завершении возвращает причину выхода. */
int Agent::StartWork ()
{

  int work_result=AG_GOOD;
  while ( ( work_result!=AG_EXIT ) && ( work_result!=AG_BAD_NAME ) && ( work_result!=AG_BAD_SRV_ADDR ) && ( work_result!=AG_FAIL_AUTH ) )
  {
    work_result=Connect();
    if ( work_result==AG_GOOD )
      work_result=Auth();
    if ( work_result==AG_GOOD )
      work_result=StartQuest();
    else
      if ( ( work_result==TEMP_BUSY ) || ( work_result==AG_FAIL_CONNECT ) ) //пытаемся переподключаться если сервер занят
        sleep ( 30 );
  }
  return work_result;
}
int  Agent::ReadConfig ( string filename )
{
  ifstream  conf_file ( filename.c_str() );
  if ( !conf_file.good() )
  {
    cout<<"file not found. default settings used"<<endl; //читаем конфиг
    return -1;
  }
  else
  {
    conf_file>>m_Name;
    conf_file>>m_SrvName;
    conf_file>>m_Address;
    conf_file>>m_Port;
    conf_file>>m_secret_adres;
  }
  conf_file.close();
  return 0;
}
/*добавляет результат в список на отправление*/
void Agent::AddResult ( Post *  result )
{
  result->LetNum();
  pthread_mutex_lock ( &m_query_mutex ); 
  m_PostList.push_back ( result ); 
  pthread_mutex_unlock ( &m_query_mutex );
}

/* * соединяется с сервером по tcp */
int Agent::Connect ( )
{
  if ( ( m_Soket=socket ( PF_INET, SOCK_STREAM,0 ) ) ==-1 )
    return AG_BAD_SOCKET; //создаемся
  struct sockaddr_in serv_adres;
  memset ( &serv_adres,0, sizeof ( serv_adres ) ); //зануляем под структуру
  serv_adres.sin_family=AF_INET;
  serv_adres.sin_port=htons ( m_Port ); //порт циферкой и только
  if ( struct hostent * phe = gethostbyname ( m_Address.c_str() ) )  //для понимания всякого вида имен
    memcpy ( &serv_adres.sin_addr, phe->h_addr, phe->h_length );
  else
    if ( ( serv_adres.sin_addr.s_addr = inet_addr ( m_Address.c_str() ) ) == INADDR_NONE )
    {
      cout<<"serv adres resolving: "<<strerror ( errno ) <<endl;
      close ( m_Soket );
      m_Soket=-1;
      return AG_BAD_SRV_ADDR;
    }
  if ( connect ( m_Soket, ( struct sockaddr* ) &serv_adres,sizeof ( struct sockaddr ) ) ==-1 )
  {
    cout<<"connect: "<<strerror ( errno ) <<endl;
    close ( m_Soket );
    m_Soket=-1;
    return AG_FAIL_CONNECT;
  }
  cout<<"connected on"<<serv_adres.sin_port<<endl;
  return AG_GOOD; //все чудесно.
}

int  Agent::Auth()  //авторизуется и возвращает код
{
  // начинаем общение
  //принимаем SRV_INTRO
  if ( recv ( m_Soket,&m_HRBuf,sizeof ( m_HRBuf ),MSG_WAITALL ) <1 )
    cout<<strerror ( errno ) <<endl;
  if ( m_HRBuf.type!=SRV_INTRO ) //это значит не пришло INTRO
  {
    close ( m_Soket );
    m_Soket=-1;
    return AG_BAD_INTRO;
  }
  if ( recv ( m_Soket, m_RBuf,ntohs ( m_HRBuf.msg_size ),MSG_WAITALL ) <1 )
    cout<<strerror ( errno ) <<endl;
  //поверяем что сервер правильно назван.
  string sr ( pintro->srv_name );
  if ( sr!=m_SrvName )
  {
    //если имя сервера  не совпало
    close ( m_Soket );
    m_Soket=-1;
    return AG_BAD_NAME;
  }
  //*отправляем  CL_LOGIN**/
  strcpy ( plogin->cl_name, m_Name.c_str() ); //заполняем структуру
  plogin->session_id=m_SessionId;
  ifstream  pass_file ( m_secret_adres.c_str() ); //читаем пароль
  md5_state_t mds;
  md5_byte_t md5rez[16];//=plogin->MD5; //заполняем структуру
  md5_init ( &mds );
  md5_append ( &mds, ( md5_byte_t* ) & ( pintro->rand_num ),sizeof ( long ) ); //генерируем хеш от рандома
  md5_append ( &mds, ( md5_byte_t* ) ( pintro->srv_name ),strlen ( ( pintro->srv_name ) ) ); //генерируем хеш от имени серва
  md5_append ( &mds, ( md5_byte_t* ) ( plogin->cl_name ),strlen ( ( plogin->cl_name ) ) ); //генерируем хеш от имени агента
  if ( pass_file.good() )
  {
    pass_file>>m_secret;
    pass_file.close();
  }
  md5_append ( &mds, ( md5_byte_t* ) ( m_secret.c_str() ),m_secret.size() ); //генерируем хеш от пароля
  md5_finish ( &mds,md5rez );
  m_secret.clear(); //очищаем пароль
  for ( int i=0;i<16;i++ )
    plogin->MD5[i]=md5rez[i];
  m_HSBuf.type=CL_LOGIN;
  m_HSBuf.msg_size=htons ( m_Name.size() +25 ); //считая нуль-терминатор
  send ( m_Soket,&m_HSBuf,sizeof ( m_HSBuf ),0 );
  send ( m_Soket,&m_SBuf, ntohs ( m_HSBuf.msg_size ),0 );
  //принимаем SRV_SES_START || SRV_DISCONNECT
  if ( recv ( m_Soket,&m_HRBuf,sizeof ( m_HRBuf ),MSG_WAITALL ) <1 )  cout<<strerror ( errno ) <<endl;
  if ( recv ( m_Soket, m_RBuf,ntohs ( m_HRBuf.msg_size ),MSG_WAITALL ) <1 )  cout<<strerror ( errno ) <<endl;
  switch ( m_HRBuf.type )
  {
    case SRV_SES_START:
      m_SessionId=psesstart->session_id;
      break;
    case SRV_DISCONNECT:
      cout<<"disconnected: "<<pdisconnect->reason<<endl;
      close ( m_Soket );
      m_Soket=-1;
      return AG_FAIL_AUTH; //возвращам почему нельзя.
      break;
    default:
      close ( m_Soket );
      m_Soket=-1;
      return AG_BAD_MSG; //пришел не тот тип сообщений
  }
  return AG_GOOD; //все прекрасно
}
/*
 * отсылает собраные результаты в БД.
 * отправляет все имеющиеся результаты тестов и накопившиеся сетевые события.
 * для внутреннего удобства.
 */
void*  Agent::SecThread ( void * pthis )
{
  Agent * a= ( Agent* ) pthis;
  a->SendResult();
  return NULL;
}
void Agent::SendResult ( )
{
  while ( !m_time_to_die )
  {
    if ( ( m_PostList.empty() ) || ( m_PostList.back()->getSeq() ==m_cur_post ) )
    {
      usleep ( 200 );
      continue;
    }
    list<Post*>::iterator it=m_PostList.begin();
    while ( ( *it )->getSeq() <= m_cur_post )
      it++;
    pthread_mutex_unlock ( &m_query_mutex );
    //проверка на тип.
    while ( it!=m_PostList.end() )
    {
      if(m_PostList.size()>=1500000)
      {
        delete *it;
        it=m_PostList.erase(it);
      }
      switch ( ( *it )->getClassID() )
      {
        case EVENT:
        {
          NetEvent * ev= static_cast<NetEvent *> ( * it );
          //тут забросать данные в буфер
          pthread_mutex_lock ( &send_mut );
          m_HSBuf.type=CL_EVENT_LOG;
          m_HSBuf.msg_size=htons ( sizeof ( eventlog_s ) );
          peventlog->probe_id= ( ev )->getIdProbe();
          peventlog->timestamp.tv_sec= htonl ( ( ev )->getTime().tv_sec );
          peventlog->timestamp.tv_usec= htonl ( ( ev )->getTime().tv_usec );
          peventlog->event_seq= htonl ( ( ev )->getSeq() );
          peventlog->cycle_num= htonl ( ( ev )->getCycleNum() );
          peventlog->adres= ( ev )->getAdress();
          peventlog->event_type= ( ev )->getEventType();
          peventlog->event_class= ( ev )->getEvClass();
          if ( SendBuf() ==AG_BAD_CONNECT )
          {
            m_cur_post=m_next_result;
            pthread_mutex_unlock ( &send_mut );
            cout<<"bad send:"<<strerror ( errno ) <<endl;
            break;
          }
          pthread_mutex_unlock ( &send_mut );
          m_cur_post= ( ev )->getSeq();
          break;
        }
        case RESULT:
        {
          NetResult* res= static_cast<NetResult *> ( * it );
          cout<<"result cycle"<<res->getCycleNum()<<endl;
          for(int i=0;i<res->getCount();i++)
             cout<<res->getResult(i)<<"  ";
          cout<<endl;
          //тут забросать данные в буфер
          pthread_mutex_lock ( &send_mut );
          m_HSBuf.type=CL_PROBE_RESULT;
          m_HSBuf.msg_size=htons ( sizeof ( idprobe_t ) + ( res )->getCount() *sizeof ( node_result_t ) + 2* sizeof ( long int ) + sizeof ( timestamp_t ) );
          pproberesult->probe_id= ( res )->getIdProbe();
          peventlog->timestamp.tv_sec= htonl ( ( res )->getTime().tv_sec );
          peventlog->timestamp.tv_usec= htonl ( ( res )->getTime().tv_usec );
          pproberesult->result_seq= htonl ( ( res )->getSeq() );
          pproberesult->cycle_num= htonl ( ( res )->getCycleNum() );
          for ( unsigned  i=0 ;i< ( ( res )->getCount() ) ;i++ )
          {
            node_result_t tmp=htonl( ( res )->getResult(i) );
            pproberesult->result[i]= tmp;
          }
          if ( SendBuf() ==AG_BAD_CONNECT )
          {
            m_cur_post=m_next_result;
            pthread_mutex_unlock ( &send_mut );
            cout<<"bad send:"<<strerror ( errno ) <<endl;
            break;
          }
          pthread_mutex_unlock ( &send_mut );
          m_cur_post= ( res )->getSeq();
          break;
        }
        default:
          cout<<"ALARM SENDING"<<endl;
      }
      it++;
    }
    pthread_mutex_lock ( &m_query_mutex );
    //надо урать уже принятые сервером.
    while ( ( !m_PostList.empty() ) && ( m_PostList.front()->getSeq() <m_next_result ) )
    {
      delete m_PostList.front();
      m_PostList.pop_front();
    }
    pthread_mutex_unlock ( &m_query_mutex ); //тут разлочить лист
  }
}


/*
 * запускает все зонды, указаные в задании.
 * для внутрененго использования.
 */
int  Agent::StartQuest ( )
{
  if ( ( pthread_create ( &m_r_thread, NULL, & ( Agent::SecThread ),this ) ) !=0 ) //в этом треде крутится отправка
  {
    return AG_BAD_SENDER;
  }
  while ( 1 )
  {
    int recrez=0;
    if ( ( recrez=recv ( m_Soket,&m_HRBuf,sizeof ( m_HRBuf ),MSG_WAITALL ) ) <1 )
    {
      cout<<strerror ( errno ) <<endl;
      KillSec();
      close ( m_Soket );
      m_Soket=-1;
      return errno;
    }
    if ( ( recrez=recv ( m_Soket, m_RBuf,ntohs ( m_HRBuf.msg_size ),MSG_WAITALL ) ) <1 )
    {
      cout<<strerror ( errno ) <<endl;
      KillSec();
      close ( m_Soket );
      m_Soket=-1;
      return errno;
    }
    if ( recrez==0 )
    {
      KillSec();
      close ( m_Soket );
      m_Soket=-1;
      return AG_BAD_CONNECT;
    }
    switch ( m_HRBuf.type )
    {
      case SRV_GET_CL_STATE:
      {
        m_comm_seq=ntohl ( pgetclstate->serial_num );
        pthread_mutex_lock ( &send_mut );
        //тут формируем в буфер отсылателя
        m_HSBuf.type=CL_STATE;
        pclientstate->serial_num=htonl ( m_comm_seq );
        gettimeofday( & ( pclientstate->curr_time ), NULL );
        pclientstate->prev_comm_time.tv_sec=htonl ( last_comm_time.tv_sec );
        pclientstate->prev_comm_time.tv_usec=htonl ( last_comm_time.tv_usec );
        pclientstate->prev_state_time.tv_sec=htonl ( last_request_time.tv_sec );
        pclientstate->prev_state_time.tv_usec=htonl ( last_request_time.tv_usec );
        pclientstate->probe_count=htonl ( m_ProbeList.size() );
        int i=0, count=0;
        for ( list<Probe*>::iterator  it=m_ProbeList.begin();it!=m_ProbeList.end();it++ )
        {
          //заполняем структуры под каждый зонд
          pclientstate->probes[i].Probe_id= ( *it )->GetIdProbe();
          pclientstate->probes[i].cycle_num=htonl ( ( *it )->getNumber() );
          pclientstate->probes[i].probe_status = ( *it )->getStatus();
          //и считаем кол-во активных
          if ( pclientstate->probes[i].probe_status != PS_PHANTOM )
          {
            count ++;
            if ( pclientstate->probes[i].probe_status != PS_STOPED )
              i++;
          }
        }
        pclientstate->active_probe_count=count;
        m_HSBuf.msg_size=htons ( sizeof ( clientstate_s ) - ( sizeof ( probe_state_s ) * ( MAX_PROBES- m_ProbeList.size() ) ) );
        //и отсылаем.
        if ( SendBuf() ==AG_BAD_CONNECT )
        {
          m_cur_post=m_next_result;
          cout<<"send: "<<strerror ( errno ) <<endl;
          close ( m_Soket );
          m_Soket=-1;
          pthread_mutex_unlock ( &send_mut );
          KillSec();
          return AG_BAD_CONNECT;
        }
        pthread_mutex_unlock ( &send_mut );
        gettimeofday(&last_request_time, NULL );
        break;
      }
      case SRV_SET_PROBE:
      {
        gettimeofday(&last_comm_time, NULL );
        if ( psetprobe->state==PR_REMOVE )
        {
          for ( list<Probe*>::iterator iter=m_ProbeList.begin();iter!=m_ProbeList.end(); iter++ )
            if ( ( *iter )->GetIdProbe() == psetprobe->Id_Probe )
            {
              delete *iter;
              iter=m_ProbeList.erase ( iter );
              iter--;
            }
          break; //это выход из свитчя
        }
        probe_status_t st=PS_STOPED;
        if ( psetprobe->state==PR_PASSIVE ) st=PS_PHANTOM;

        Probe * P1 = new Probe ( m_pinger,psetprobe->Id_Probe,st,psetprobe->target,ntohl ( psetprobe->count ),ntohs ( psetprobe->size ),ntohl ( psetprobe->interval ) );
        if ( P1->getStatus() ==PS_BROKEN ) delete P1;
        else
        {
          m_ProbeList.push_back ( P1 );
          P1->Start();
        }
        break;
      }
      case SRV_DATA_ACK:
      {
        //принять значения
        m_next_result=ntohl ( pdataack->result_seq )+1;
        break;
      }
      case SRV_DISCONNECT:
        cout<<"disconnected: "<<pdisconnect->reason<<endl;
        close ( m_Soket );
        m_Soket=-1;
        KillSec();
        return  AG_EXIT; //возвращам почему вышли.
        break;
      default:
        break; //пришел не тот тип сообщений
    }
  }
  KillSec();
  return AG_GOOD;
}
void Agent::KillSec() //уничтожает привязаный второй поток
{
  m_time_to_die=1;
  pthread_join ( m_r_thread,NULL );
}
int Agent::SendBuf()
{
  int sres, hsres;
  if ( ( hsres=send ( m_Soket,&m_HSBuf,sizeof ( m_HSBuf ),0 ) ) <1 )
    return AG_BAD_CONNECT;
  if ( ( sres=send ( m_Soket,m_SBuf,ntohs ( m_HSBuf.msg_size ),0 ) ) <1 )
    return AG_BAD_CONNECT;
  else
    return sres;
}
