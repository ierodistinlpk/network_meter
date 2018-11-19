/***************************************************************************
 *   Copyright (C) 2009 by IERO   *
 *   iero@localhost   *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <list>
#include <errno.h>
#include <time.h>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/nontransaction>
#include "../../agent_nix/src/datatypes.h"
#include <secretarsha_Lena.h>
#include "mortuary_janitor.h"
using namespace std;
using namespace pqxx;

int testDB ( string constr );
int main ( int argc, char *argv[] )
{
  if ( argc!=2 )
  {
    cout<<"usage: halfserv config.file \n        exiting.\n";
    return 0;
  }
  srand ( time ( NULL ) );
  config Config;
  if ( !Config.ReadCFG (string(argv[1]) ) )
  {
    cout<<"i'm stoped"<<endl;
    return 0;
  }
  if ( !Config.Use_secret() )
  {
    cout<<"i'm stoped"<<endl;
    return 0;
  }
  if ( !testDB ( Config.Connstring() ) )
  {
    cout<<"i'm stoped"<<endl;
    return 0;
  }

  int sock=-1;
  list<secretarsha_Lena*> Secretary_List;
  Mortuary_Jaintor killer ( &Secretary_List ); //уборщик трупов
  if ( ( sock=socket ( PF_INET, SOCK_STREAM,0 ) ) ==-1 ) cout<<-1<<endl; //создаемся
  struct sockaddr_in serv_adres;
  memset ( &serv_adres,0, sizeof ( serv_adres ) ); //зануляем под структуру
  serv_adres.sin_family=AF_INET; //
  serv_adres.sin_port=htons ( Config.Port() ); //порт циферкой
  serv_adres.sin_addr.s_addr=INADDR_ANY;
  if ( bind ( sock, ( struct sockaddr* ) &serv_adres,sizeof ( serv_adres ) ) ==-1 )    //биндимся
  {
    cout<<"bind: "<<strerror ( errno ) <<endl;
   return 0 ;
  }
  if ( listen ( sock,Config.Accept_count() ) ==-1 ) //слушаем
  {
    cout<<"listen: "<<strerror ( errno ) <<endl;
    return 0 ;
  }
  //int cur_sock;
  struct sockaddr_in clientaddr;
  memset ( &clientaddr,0, sizeof ( sockaddr_in ) );
  socklen_t  clientaddrlen=sizeof ( clientaddr );
  while ( 1 )
  {
    int cur_sock= accept ( sock, ( struct sockaddr* ) &clientaddr,&clientaddrlen ); //работа с одним агентом
    if ( cur_sock==-1 ) { cout<<"accept: "<<strerror ( errno ) <<endl; continue;}
    secretarsha_Lena* Vasya=new secretarsha_Lena ( cur_sock, &Config );
    if ( Vasya->Status() ) delete Vasya;
    else Secretary_List.push_back ( Vasya );
    /// //////////////////////////////////////
    cout<<"ready"<<endl;
  }
  close ( sock );
  return EXIT_SUCCESS;
}

int testDB ( string constr )
{
  try
  {
    connection conn ( constr );
    nontransaction w ( conn,"testDB" );
    result r=w.exec ( "select count(*) from agent join probe on probe.name=agent.name" );
    cout<<"all right 1"<<endl;
  }
  catch ( broken_connection& e )
  {
    cout<<"DB connection failed"<<endl;
    return 0;
  }
  catch ( sql_error& e )
  {
    cout<<"DB content wrong"<<endl;
    return 0;
  }
  return 1;
}

int config::ReadCFG ( string constr )
{

  ifstream file ( constr.c_str() );
  if ( !file.good() )
  {
    cout<<"config file : "<<strerror ( errno ) <<endl;
    return 0;
  }
  file>>name;
  file>>port;
  file>>accept_count;
  file>>state_interval;
  file>>db_host;
  file>>db_port;
  file>>db_name;
  file>>db_user;
  file>>secret>>ws;
  file.close();
  return 1;
}
int config::Use_secret()
{
  ifstream file ( secret.c_str() );
  if ( !file.good() )
  {
    cout<<"bad secret file : "<<strerror ( errno ) <<endl;
    return 0;
  }
  file>>secret;
  file.close();
  ostringstream conn ( "" );
  conn<< "host=" << db_host
  << " user=" << db_user
  << " password=" << secret
  << " dbname=" << db_name;
  connstring=conn.str();
  return 1;
}
