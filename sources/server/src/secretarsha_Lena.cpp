#include "secretarsha_Lena.h"
#include "md5.h"
#include "mortuary_janitor.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>

pthread_cond_t Mortuary_Jaintor::handle;
pthread_mutex_t Mortuary_Jaintor::handle_mutex;
int   tv_sub ( timestamp_t out, timestamp_t in ) ;
/*********************************/
secretarsha_Lena::secretarsha_Lena ( sock soket, config * Config ) :m_die_status ( 0 ), m_socket ( soket )
{
  pthread_mutex_init ( &inner_mutex, NULL );
  //указазаетли для отправки
  pintro= ( intro_s* ) m_SBuf;
  psesstart= ( sesstart_s* ) m_SBuf;
  pdisconnect= ( disconnect_s* ) m_SBuf;
  pgetclstate= ( getclstate_s* ) m_SBuf;
  psetprobe= ( setprobe_s* ) m_SBuf;
  pdataack= ( dataack_s* ) m_SBuf;
  //указатели для приема
  plogin= ( login_s* ) m_RBuf;
  pclientstate = ( clientstate_s* ) m_RBuf;
  pproberesult= ( proberesult_s* ) m_RBuf;
  peventlog= ( eventlog_s* ) m_RBuf;
  pclientdisconnect= ( cl_disconnect* ) m_RBuf;
  initAttributes();
  Conf = Config;
  if ( ( pthread_create ( &main_thr, NULL, & ( secretarsha_Lena::FstThread ),this ) ) !=0 )
    m_die_status=1;
}

secretarsha_Lena::~secretarsha_Lena ( )
{
  m_die_status=1;
  pthread_join ( main_thr, NULL );
  close ( m_socket );
  pthread_mutex_destroy ( &inner_mutex );
}
/** * поток с авторизацией и приемом данных */
void secretarsha_Lena::main_thread ( )
{
  int res=Auth();
  if ( res!=SR_GOOD )
  {
    m_die_status=1;
    close ( m_socket );
    m_socket=-1;
    pthread_mutex_lock ( &Mortuary_Jaintor::handle_mutex );
    pthread_cond_signal ( &Mortuary_Jaintor::handle );
    pthread_mutex_unlock ( &Mortuary_Jaintor::handle_mutex );
    pthread_exit ( NULL );
  }
  if ( ( pthread_create ( &ctl_thr, NULL, & ( secretarsha_Lena::SecThread ),this ) ) !=0 )
  {
    //послать дисконект по причине внутренней ошибки
    pdisconnect->code=TEMP_BUSY;
    strcpy ( pdisconnect->reason,"internal thread error" );
    m_HSBuf.type=SRV_DISCONNECT;  //заполняем хедер посылки
    m_HSBuf.msg_size=htons ( strlen ( "internal thread error" ) +2 );
    send ( m_socket,&m_HSBuf,sizeof ( m_HRBuf ),0 ); //посылаем хедер
    send ( m_socket,&m_SBuf,ntohs ( m_HSBuf.msg_size ),0 ); //посылаем интро
    cout<<"disconect sended  "<<m_socket<<endl;
    m_die_status=1;
    close ( m_socket );
    m_socket=-1;
    pthread_mutex_lock ( &Mortuary_Jaintor::handle_mutex );
    pthread_cond_signal ( &Mortuary_Jaintor::handle );
    pthread_mutex_unlock ( &Mortuary_Jaintor::handle_mutex );
    pthread_exit ( NULL );
  }
  //тут начать злостный ресив.
  if( ( StartContact() ==SR_EXIT )|| ( StartContact() ==SR_BAD_CONNECT ))
  {
    //умирать с выходом состояния.
    m_die_status=1;
    pthread_join ( ctl_thr,NULL );
    PutState();
    close ( m_socket );
    m_socket=-1;
    pthread_mutex_lock ( &Mortuary_Jaintor::handle_mutex );
    pthread_cond_signal ( &Mortuary_Jaintor::handle );
    pthread_mutex_unlock ( &Mortuary_Jaintor::handle_mutex );
    pthread_exit ( NULL );
  }
}


/*получает авторизацию клиента.между делом  - лезем в список померших либо заводим заново. */
int secretarsha_Lena::Auth ( )
{
  //отправляем SRV_INTRO
  pintro->rand_num=rand(); //генерируем случайное число
  strcpy ( ( char* ) ( pintro->srv_name ),Conf->Name().c_str() ); // пишем имя
  m_HSBuf.type=SRV_INTRO;  //заполняем хедер посылки
  m_HSBuf.msg_size=htons ( sizeof ( long ) +strlen ( pintro->srv_name ) +1 );
  send ( m_socket,&m_HSBuf,sizeof ( m_HRBuf ),0 ); //посылаем хедер
  send ( m_socket,&m_SBuf,ntohs ( m_HSBuf.msg_size ),0 ); //посылаем интро
  cout<<"intro sended  "<<endl;
  //принимаем CL_LOGIN
  if ( recv ( m_socket,&m_HRBuf,sizeof ( m_HRBuf ),MSG_WAITALL ) <1 ) { cout<<strerror ( errno ) <<endl; }//принимаем хедер
  if ( m_HRBuf.type!=CL_LOGIN ) { cout<<"alarm!!!"<<m_HRBuf.type<<endl;    close ( m_socket ); return SR_BAD_MSG;} //пришло нечто кроме логина
  if ( recv ( m_socket, m_RBuf,htons ( m_HRBuf.msg_size ),MSG_WAITALL ) <1 )  cout<<strerror ( errno ) <<endl; //принимает логин
  //проверяем есть ли в списке
  try
  {
   
    pqxx::connection main_conn ( Conf->Connstring() );
    pqxx::nontransaction w ( main_conn,"Auth" );
    string query="select passkey from agent where name = '";
    query=query+string ( plogin->cl_name )+"'";
    pqxx::result r=w.exec ( query );
    if ( r.empty() )
    {
      //послать дисконект
      pdisconnect->code=BAD_LOGIN;
      strcpy ( pdisconnect->reason,"your name not found" );
      m_HSBuf.type=SRV_DISCONNECT;  //заполняем хедер посылки
      m_HSBuf.msg_size=htons ( strlen ( "your name not found" ) +2 );
      if ( SendBuf() <1 )
      {
        cout<<m_client_name<<"disconnect failed by sock"<<endl;
        return SR_BAD_CONNECT;
      }
      cout<<m_client_name<<"disconect sended  "<<endl;
      close ( m_socket );
      m_socket=-1;
      return SR_FAIL_AUTH;
    }
    string secret= r.front().front().c_str();
    //считаем от принятого MD5 и сверяем
    md5_state_t mds;
    md5_byte_t md5rez[16]; //заполняем структуру
    md5_init ( &mds );
    md5_append ( &mds, ( md5_byte_t* ) & ( pintro->rand_num ),sizeof ( long ) ); //генерируем хеш от рандома
    md5_append ( &mds, ( md5_byte_t* ) ( pintro->srv_name ),strlen ( ( pintro->srv_name ) ) ); //генерируем хеш от имени серва
    md5_append ( &mds, ( md5_byte_t* ) ( plogin->cl_name ),strlen ( ( plogin->cl_name ) ) ); //генерируем хеш от имени агента
    md5_append ( &mds, ( md5_byte_t* ) ( secret.c_str() ),secret.size() ); //генерируем хеш от пароля
    md5_finish ( &mds,md5rez );
    secret.clear(); //очищаем пароль
    m_client_name= ( plogin->cl_name );
    if ( strncmp ( ( char* ) md5rez, ( char* ) ( plogin->MD5 ),16 ) !=0 ) //авторизация провалена
    {
      //отправляем SRV_DISCONNECT
      //и рвем соединение
      pdisconnect->code=BAD_LOGIN;
      strcpy ( pdisconnect->reason,"bad authentication" );
      m_HSBuf.type=SRV_DISCONNECT;  //заполняем хедер посылки
      m_HSBuf.msg_size=htons ( strlen ( "bad authentication" ) +2 );
      if ( SendBuf() <1 )
      {
        cout<<m_client_name<<"disconnect failed by sock"<<endl;
        return SR_BAD_CONNECT;
      }
      cout<<m_client_name<<"disconect sended  "<<endl;
      close ( m_socket );
      m_socket=-1;
      return SR_FAIL_AUTH;
    }
    //отправляем SRV_SES_START
    psesstart->session_id=SearchState();
    if ( psesstart->session_id==0 )
    {
      //значит не получилось
      return send_disconnect ( INTERNAL_ERROR,"cannot create session" );
    }
    m_HSBuf.type=SRV_SES_START;  //заполняем хедер посылки
    m_HSBuf.msg_size=htons ( sizeof ( long long ) );
    if ( SendBuf() <1 )
    {
      cout<<m_client_name<<"sesionstart failed by sock"<<endl;
      return SR_BAD_CONNECT;
    }
    cout<<m_client_name.c_str() <<"sesionstart sended  "<<m_socket<<endl;
    return SR_GOOD;
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"DB exception: "<<e.what();
    return send_disconnect ( INTERNAL_ERROR, "database exception" );
  }
  catch ( ... )
  {
    cout<<"DB exception: ";
    return send_disconnect ( INTERNAL_ERROR, "database exception" );
  }
  return SR_GOOD;
}

/** принимает данные сервера  */
int secretarsha_Lena::StartContact ( )
{

  while ( 1 )
  {
    if ( RecvBuf() <1 )
      return SR_BAD_CONNECT;
    switch ( m_HRBuf.type )
    {
      case CL_STATE:
      {
        cout<<"SIZE="<<ntohs ( m_HRBuf.msg_size );
        m_ses_state.probe_count=ntohl ( pclientstate->probe_count );
        m_ses_state.active_probe_count=ntohl ( pclientstate->active_probe_count );
        m_ses_state.last_event=ntohl ( pclientstate->event_log_num );
        m_ses_state.m_cl_state_seq=ntohl ( pclientstate->serial_num );
        m_ses_state.cl_time.tv_sec=ntohl ( pclientstate->curr_time.tv_sec ); //время агента
        m_ses_state.cl_time.tv_usec=ntohl ( pclientstate->curr_time.tv_usec );
        m_ses_state.cl_comm_time.tv_sec=ntohl ( pclientstate->prev_comm_time.tv_sec ); //времмммя команды
        m_ses_state.cl_comm_time.tv_usec=ntohl ( pclientstate->prev_comm_time.tv_usec );
        m_ses_state.cl_state_time.tv_sec=ntohl ( pclientstate->prev_state_time.tv_sec ); //времмммя запроса
        m_ses_state.cl_state_time.tv_usec=ntohl ( pclientstate->prev_state_time.tv_usec );
        m_ses_state.ProbeList.clear();
        for ( unsigned i=0;i<m_ses_state.probe_count;i++ )
        {
          ProbeState probe ( pclientstate->probes[i].Probe_id,ntohl ( pclientstate->probes[i].cycle_num ),pclientstate->probes[i].probe_status );
          m_ses_state.ProbeList.push_back ( probe );
        }
        // проверить списки на соответствие
        CheckProbes();
        //обновить состояние в БД
        UpdateState();
        cout<<"state received"<<endl;
        break;
      }
      case CL_PROBE_RESULT:
      {
        //создавать результ и обрабатывать
        if(m_ses_state.next_result<ntohl(pproberesult->result_seq))
        {
        unsigned long count= ( ntohs ( m_HRBuf.msg_size ) - ( sizeof ( proberesult_s ) - ( MAX_COUNT  *sizeof ( node_result_t ) ) ) ) /sizeof ( node_result_t );
        InsertResult ( count );
        m_ses_state.next_result=ntohl(pproberesult->result_seq);
        cout<<"result recved: "<<count<<endl;
        }
        break;
      }
      case CL_EVENT_LOG:
      {
        //записать евент
        if(m_ses_state.next_result<ntohl(peventlog->event_seq))
        {
          InsertEvent();
          m_ses_state.next_result=ntohl(peventlog->event_seq);
          cout<<"event recved: "<<ntohl(peventlog->cycle_num)<<endl;
        }
        break;
      }
      case CL_DISCONNECT:
      {
        //умирать с возвратом что все идет по плану
        PutState();
        return SR_EXIT;
        break;
      }
      default:
        //писать в лог что присылали непонятное
        cout<<"unknown data"<<endl;
        break;
    }
  }
  PutState();
  return SR_GOOD;
}


/** * поток отправляющий агенту управляющие данные
*/
void secretarsha_Lena::ctl_thread ( )
{
  while ( !m_die_status )
  {
    pthread_mutex_lock ( &inner_mutex );
    //отправка номеров принятых послед-тей
    m_HSBuf.type=SRV_GET_CL_STATE;
    m_HSBuf.msg_size=htons ( sizeof ( getclstate_s ) );
    pgetclstate->serial_num=htonl ( m_ses_state.m_state_seq );
    m_ses_state.m_state_seq++;
    if ( SendBuf() <1 )
      cout<<m_client_name<<"get state failed by sock"<<endl;
    //запрос статуса
    m_HSBuf.type= SRV_DATA_ACK;
    m_HSBuf.msg_size=htons ( sizeof ( dataack_s ) );
    pdataack->result_seq=htonl ( m_ses_state.next_result );
    if ( SendBuf() <1 )
      cout<<m_client_name<<"ack failed by sock"<<endl;
    pthread_mutex_unlock ( &inner_mutex );
    for ( unsigned i=0;i<Conf->State_interval();i++ )
    {
      sleep ( 1 );
      if ( m_die_status )
        return;
    }
  }
}
void secretarsha_Lena::initAttributes ( )
{
  pintro= ( intro_s* ) m_SBuf;
  psesstart= ( sesstart_s* ) m_SBuf;
  pdisconnect= ( disconnect_s* ) m_SBuf;
  pgetclstate= ( getclstate_s* ) m_SBuf;
  psetprobe= ( setprobe_s* ) m_SBuf;
  pdataack= ( dataack_s* ) m_SBuf;
  plogin = ( login_s * ) m_RBuf;
  pclientstate = ( clientstate_s * ) m_RBuf ;
  pproberesult= ( proberesult_s * ) m_RBuf;
  peventlog = ( eventlog_s * ) m_RBuf;
  pclientdisconnect = ( cldisconnect_s * ) m_RBuf;
  memset ( &m_HRBuf,0, sizeof ( m_HRBuf ) );
  memset ( &m_RBuf,0, DBUF_SIZE );
  memset ( &m_HSBuf,0, sizeof ( m_HSBuf ) );
  memset ( &m_SBuf,0, DBUF_SIZE );
}

void * secretarsha_Lena::FstThread ( void * pthis )
{
  ( ( secretarsha_Lena* ) pthis )->main_thread();
  return NULL;
}
void * secretarsha_Lena::SecThread ( void * pthis )
{
  ( ( secretarsha_Lena* ) pthis )->ctl_thread();
  return NULL;
}
/*складывает в БД состояние клиента при обрыве связи*/
int secretarsha_Lena::PutState()
{
  try
  {
  pqxx::connection main_conn ( Conf->Connstring() );
  pqxx::work w ( main_conn,"state" );
  //формируем представление времени
  stringstream tmp ( "" );
  tmp<<"."<<ntohl ( pclientstate->curr_time.tv_usec ) /1000;
  time_t timesecs= ( ntohl ( pclientstate->curr_time.tv_sec ) );
  string timer=ctime ( &timesecs );
  timer.insert ( 19,tmp.str() );
  timestamp_t serv_time;
  gettimeofday(&serv_time,NULL );
  long time_seek = tv_sub ( pclientstate->curr_time,serv_time )/1000;
  //запрос
  ostringstream query ( "" );
  query<<"update session SET end_time= '"<<timer<<"' , next_seq="<<m_ses_state.next_result<<" , time_seek="<<time_seek<< "where \"ID_SESSION\" = "<<m_ses_state.m_sessionId;
  pqxx::result r=w.exec ( query.str() );
  w.commit();
  return SR_GOOD;
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"DB exception: "<<__func__<<e.what();
    return send_disconnect ( INTERNAL_ERROR, "database exception" );
  }
  catch ( ... )
  {
    return SR_BAD_SESSION;
  }
}
/*ищет состояние клиента с принятым ID и забирает его из БД*/
long long secretarsha_Lena::SearchState()
{
  try
  {
    pqxx::connection main_conn ( Conf->Connstring() );
    pqxx::work w ( main_conn,"Auth" );
    pqxx::result r;
    if ( plogin->session_id!=0 )
    {
      ostringstream query ( "" );
      query<<"select next_seq , time_seek from session where \"ID_SESSION\" = "<<plogin->session_id<<" and name="<<m_client_name;
      r=w.exec ( query.str() );
      if ( !r.empty() )
      {
        m_ses_state.m_sessionId=plogin->session_id;
        m_ses_state.next_result=atol ( r.front() [0].c_str() );
        m_ses_state.time_seek=atol ( r.front() [1].c_str() );
        return m_ses_state.m_sessionId;
      }
    }
    //иначе - никого нету и создать новую.
    ostringstream query ( "" );
    query<<"insert into session (name, start_time) values ( '"<<m_client_name<<"' , CURRENT_TIMESTAMP  )";
    r=w.exec ( query.str() );
    if ( r.affected_rows() ==1 )
    {
      ostringstream quer ( "" );
      // упорядочивая по убыванию времени получаем первым в выборке нужный элемент.
      quer<<"select \"ID_SESSION\" from session where name= '"<<m_client_name<<"' order by start_time desc";
      r=w.exec ( quer.str() );
      m_ses_state.m_sessionId=atoll ( r.front() [0].c_str() );;
      m_ses_state.next_result=0;
      m_ses_state.time_seek=0;
      w.commit();
      return m_ses_state.m_sessionId;
    }
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"DB exception: "<<__func__<<e.what();
    return send_disconnect ( INTERNAL_ERROR, "database exception" );
  }
  catch ( ... )
  {
    return SR_BAD_SESSION;
  }
  return SR_BAD_SESSION;
}

int secretarsha_Lena::SendBuf()
{
  int sres, hsres;
  if ( ( ( hsres=send ( m_socket,&m_HSBuf,sizeof ( m_HSBuf ),0 ) ) <1 ) || ( ( sres=send ( m_socket,m_SBuf,ntohs ( m_HSBuf.msg_size ),0 ) ) <1 ) )
    return SR_BAD_CONNECT;
  else
    return sres;
}

int secretarsha_Lena::RecvBuf()
{
  int sres, hsres;
  if ( ( hsres=recv ( m_socket,&m_HRBuf,sizeof ( m_HRBuf ), MSG_WAITALL ) ) <1 )
    return SR_BAD_CONNECT;
  if ( ( sres=recv ( m_socket,m_RBuf,ntohs ( m_HRBuf.msg_size ),MSG_WAITALL ) ) <1 )
    return SR_BAD_CONNECT;
  return sres;
}
/*вставляет в БД записи о результате*/
int secretarsha_Lena::InsertResult ( unsigned long count )
{
  try
  {
    /// ////////////////////////////////проетстить на спец. обученых данных
    pqxx::connection main_conn ( Conf->Connstring() );
    pqxx::work w ( main_conn,"Auth" );
    pqxx::result r;
    // перевод времени в строку
    stringstream tmp ( "" );
    tmp<<"."<<ntohl ( pproberesult->timestamp.tv_usec );
    time_t timesecs= ( ntohl ( pproberesult->timestamp.tv_sec ) );
    string timer=ctime ( &timesecs );
    timer.insert ( 19,tmp.str() );
    //запрос на отношение result
    ostringstream query ( "" );
    query<<"insert into result values ("<<ntohl ( pproberesult->cycle_num ) <<" , '"<<timer<<"' , "<<pproberesult->probe_id<<" , " <<m_ses_state.m_sessionId<<" ) ";
    r=w.exec ( query.str() );
    for ( unsigned i=0;i<count;i++ ) //пишем пачку rtt
    {
      cout<<"insert into result_node values ( "<<i<<" , "<< (signed long)ntohl( (pproberesult->result)[i] ) <<" , "<<m_ses_state.m_sessionId<<" , "<<pproberesult->probe_id<<" , "<<ntohl ( pproberesult->cycle_num ) <<" )"<<endl;
      ostringstream query ( "" );
      query<<"insert into result_node values ( "<<i<<" , "<<(signed long)ntohl ( pproberesult->result[i] ) <<" , "<<m_ses_state.m_sessionId<<" , "<<pproberesult->probe_id<<" , "<<ntohl ( pproberesult->cycle_num ) <<" )";
      r=w.exec ( query.str() );
      if ( r.affected_rows() !=1 )
        cout<<"result insertion error"<<endl;
    }
    w.commit();
    return SR_GOOD;
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"database result exception: "<<__func__<<e.what();
  }
  catch ( ... )
  {
    return send_disconnect ( INTERNAL_ERROR,"DB exception" );
  }
  return SR_GOOD;
}

int secretarsha_Lena::InsertEvent()
{
  string err[2]={"false","true"};
  try
  {
    in_addr ad={peventlog->adres};
    pqxx::connection main_conn ( Conf->Connstring() );
    pqxx::result r;
    {
      pqxx::nontransaction w ( main_conn,"event" ); //находм нужный тип собыитя
      ostringstream prequery ( "" );
      prequery<<"select id_type from event_type where code="<< ( int ) peventlog->event_class<<" and is_err = "<<err[ ( int ) peventlog->event_type];
      r=w.exec ( prequery.str() );
    }
    if ( r.empty() ) //не найдено такого собыия в справочнике
      return SR_BAD_EVENT;
    string id_type= ( r[0][0].c_str() );
    //формируем представление времени
    stringstream tmp ( "" );
    tmp<<"."<<ntohl ( peventlog->timestamp.tv_usec ) /1000;
    time_t timesecs= ( ntohl ( peventlog->timestamp.tv_sec ) );
    string timer=ctime ( &timesecs );
    timer.insert ( 19,tmp.str() );
    //формируем запрос на добавление
    cout<<timer<<endl;
    ostringstream query ( "" );
    query<<"insert into event (\"timestp\", \"adress\", id_session, id_probe, cycle_num, \"id_type\" ) values ('" <<timer<<"' , '"<<inet_ntoa ( ad ) <<"' , "<<m_ses_state.m_sessionId<<" , "<<peventlog->probe_id<<" , "<<ntohl ( peventlog->cycle_num ) <<" , "<<id_type<<" )";
    pqxx::work w ( main_conn,"event" ); //транзакция для insert
    r=w.exec ( query.str() );
    if ( r.affected_rows() ==1 )
    {
      w.commit();
      cout<<"event inserted"<<endl;
    }
    cout<<"event inserted"<<endl;
    return SR_GOOD;
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"DB event exception: "<<__func__<<e.what();
  }
  catch ( ... )
  {
    return send_disconnect ( INTERNAL_ERROR,"database exception" );
  }
  return SR_GOOD;
}
int secretarsha_Lena::UpdateState()
{
  try
  {
    pqxx::connection main_conn ( Conf->Connstring() );
    pqxx::work w ( main_conn,"state" );
    //формируем пердставление времени
    stringstream tmp ( "" );
    tmp<<"."<<ntohl ( pclientstate->curr_time.tv_usec );
    time_t timesecs= ( ntohl ( pclientstate->curr_time.tv_sec ) );
    string timer=ctime ( &timesecs );
    timer.insert ( 19,tmp.str() );
    timestamp_t serv_time;
    gettimeofday (&serv_time,NULL );
    timestamp_t cltime;
    cltime.tv_sec=ntohl ( pclientstate->curr_time.tv_sec );
    cltime.tv_usec=ntohl ( pclientstate->curr_time.tv_usec );
    long time_seek = tv_sub ( serv_time, cltime)/1000; //считаем насколько время на сервере больше в МИЛИсекундах.
    //запрос
    ostringstream query ( "" );
    query<<"update session SET end_time= '"<<timer<<"' , next_seq="<<m_ses_state.next_result<<" , time_seek="<<time_seek<< "where \"ID_SESSION\" = "<<m_ses_state.m_sessionId;
    pqxx::result r=w.exec ( query.str() );
    if ( r.affected_rows() ==1 )
    {
      w.commit();
      cout<<"state updated"<<endl;
    }
    return SR_GOOD;
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"DB state exception: "<<__func__<<e.what();
  }
  catch ( ... )
  {
    cout<<"DB state exception: "<<__func__;
//    return send_disconnect ( INTERNAL_ERROR,"database exception" );
  }
  return SR_GOOD;
}

int  secretarsha_Lena:: CheckProbes() //возвращает -1 в случае ошибок, иначе - кол-во новых зондов
{
  list<srvProbe> IDs;
  try
  {
    pqxx::connection main_conn ( Conf->Connstring() );
    pqxx::work w ( main_conn,"Auth" );
    string query="select * from probe where  probe.name = '";
    query=query+m_client_name+"'";
    pqxx::result r=w.exec ( query );
    if ( !r.empty() )
      for ( pqxx::result::const_iterator it=r.begin(); it!=r.end();it++ )
        //выбираем все зонды в list
        IDs.push_back ( srvProbe ( atoll ( it[0].c_str() ) , atol ( it[3].c_str() ) , atol ( it[1].c_str() ), inet_addr ( it[4].c_str() ),  atoi ( it[2].c_str() ) ) );
  }
  catch ( pqxx::sql_error e )
  {
    cout<<"DB probes exception: "<<e.what();
    return send_disconnect ( INTERNAL_ERROR, "database exception" );
  }
  catch ( ... )
  {
    return send_disconnect ( INTERNAL_ERROR, "database exception" );
  }
  //для каждго  в ID ищем соответствие в state

  for ( list<ProbeState>::iterator probeit=m_ses_state.ProbeList.begin();probeit!=m_ses_state.ProbeList.end(); probeit++ )
  {
    bool flag=false;
    for ( list<srvProbe>::iterator idit=IDs.begin();idit!=IDs.end();idit++ )
    {
      if ( idit->getIdProbe() ==probeit->getIdProbe() )
      {
        idit= IDs.erase ( idit );
        idit--;
        flag=true;
      }
    }
    if ( flag )
    {
      probeit=m_ses_state.ProbeList.erase ( probeit );
      probeit--;
    }
  }
  //всех оставшихся в листе - убрать
  if ( !m_ses_state.ProbeList.empty() )
  {
    pthread_mutex_lock ( &inner_mutex );
    for ( list<ProbeState>::iterator it=m_ses_state.ProbeList.begin(); it!=m_ses_state.ProbeList.end();it++ )
    {
      m_HSBuf.type= SRV_SET_PROBE;
      m_HSBuf.msg_size=htons ( sizeof ( setprobe_s ) );
      psetprobe->Id_Probe=it->getIdProbe() ;
      psetprobe->interval=0;
      psetprobe->count=0;
      psetprobe->target=0;
      psetprobe->size = 0;
      psetprobe->state=PR_REMOVE;
      if ( SendBuf() <1 )
      {
        cout<<"setprobe failed"<<endl;
        pthread_mutex_unlock ( &inner_mutex );
        return SR_BAD_CONNECT;
      }
    }
    pthread_mutex_unlock ( &inner_mutex );
  }
  //всех в новом листе - создать.
  if ( !IDs.empty() )
  {
    pthread_mutex_lock ( &inner_mutex );
    for ( list<srvProbe>::iterator it=IDs.begin(); it!=IDs.end();it++ )
    {
      m_HSBuf.type= SRV_SET_PROBE;
      m_HSBuf.msg_size=htons ( sizeof ( setprobe_s ) );
      psetprobe->Id_Probe= it->getIdProbe( );
      psetprobe->interval=htonl ( it->getInterval ( ) );
      psetprobe->count=htonl ( it->getCount() );
      psetprobe->target= ( it->getTarget() );
      psetprobe->size = htons ( it->getSize() );
      psetprobe->state=PR_ACTIVE;
      if ( SendBuf() <1 )
      {
        cout<<"setprobe failed"<<endl;
        pthread_mutex_unlock ( &inner_mutex );
        return  SR_BAD_CONNECT;
      }
    }
    pthread_mutex_unlock ( &inner_mutex );
  }
  return IDs.size();
}


int   tv_sub ( timestamp_t out, timestamp_t in ) //возвращает микросекунды.
{
  out.tv_usec -= in.tv_usec ;   	/* out -= in */
  out.tv_sec -= in.tv_sec;
  return out.tv_sec*1000000+out.tv_usec;
}

int secretarsha_Lena::send_disconnect ( unsigned char code, string message )
{
  pthread_mutex_lock ( &inner_mutex );
  pdisconnect->code=code;
  strcpy ( pdisconnect->reason,message.c_str() );
  m_HSBuf.type=SRV_DISCONNECT;  //заполняем хедер посылки
  m_HSBuf.msg_size=htons ( strlen ( message.c_str() ) +2 );
  if ( SendBuf() <1 )
  {
    cout<<m_client_name<<"disconnect failed by sock"<<endl;
    pthread_mutex_unlock ( &inner_mutex );
    return SR_BAD_CONNECT;
  }
  cout<<m_client_name<<"disconect sended  "<<message<<endl;
  close ( m_socket );
  m_socket=-1;
  pthread_mutex_unlock ( &inner_mutex );
  return SR_EXIT;
}
