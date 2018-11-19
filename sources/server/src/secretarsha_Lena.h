
#ifndef SECRETARSHA_LENA_H
#define SECRETARSHA_LENA_H

#include <string>
#include <list>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/nontransaction>
#include "../../agent_nix/src/datatypes.h"
#include "srvProbe.h"
#include "session_state.h"
using namespace std;
/** class config. содержит в себе инфу из файла-конфига*/
class config
{
  private:
    string name;
    unsigned short port;
    int accept_count;
    string db_name;
    string db_user;
    string db_host;
    string db_port;
    unsigned state_interval;
    string secret;
    string connstring;
  public:
    string Name() const{ return name;}
    unsigned short Port() const{ return port;}
    int Accept_count() const{ return accept_count;}
    string Db_name() const{ return db_name;}
    string Db_user() const{ return db_user;}
    unsigned State_interval() const{ return state_interval;}
    string Secret() const{ return secret;}
    int ReadCFG ( string constr ); //
    string Connstring() {   return connstring;}
    int Use_secret();
};

/**  * class secretarsha_Lena  */


class secretarsha_Lena
{
  private:
    short m_die_status; //флаг завершения потоков
    pthread_t main_thr; //идентификатор основного потока
    pthread_t ctl_thr;//идентификатор второго потока
    pthread_mutex_t inner_mutex;  //мютекс на сокет
    string m_logfile;
    msg_header m_HRBuf; //header receive buffer
    msg_header m_HSBuf; //header receive buffer
    unsigned char m_SBuf[DBUF_SIZE];
    unsigned char m_RBuf[DBUF_SIZE];
    config * Conf; //данные из конфигурационного файла
    //данные о клиенте
    SessionState m_ses_state;
    string m_client_name;
    sock m_socket; //сокет связи с агентом
    //указазаетли для передачи
    intro_s* pintro;
    sesstart_s* psesstart;
    disconnect_s* pdisconnect;
    getclstate_s* pgetclstate;
    setprobe_s* psetprobe;
    dataack_s* pdataack;
    //указатели для приема
    login_s *plogin;
    clientstate_s *pclientstate ;
    proberesult_s * pproberesult;
    eventlog_s *  peventlog;
    cldisconnect_s * pclientdisconnect;
    // каждая секретутка подрубается к бд по-своему
//  void m_DBconnection;
    void main_thread ( );    /*   * поток с авторизацией и приемкой данных   */
    void ctl_thread ( );    /*   * поток отправляющий агенту управляющие данные*/
    void initAttributes ( ) ;
    int PutState(); //сохраняет состояние сеанса при обрыве связи
    long long SearchState(); //ищет состояние клиента с принятым ID в БД. возвращает ID.
    int SendBuf(); //ф-я передачи заполненного буфера
    int RecvBuf(); //ф-я приема данных из сокета
    int CheckProbes(); //проверяет список зондов и по необходимости приказывает создать/убить зонды на клиенте
    int InsertResult ( unsigned long count ); //заносит принятый результат в БД
    int InsertEvent(); //заносит принятое событие в БД
    int UpdateState(); //обновляет информацию о состоянии сеанса
    int send_disconnect ( unsigned char code, string message ); //отправляет агенту сигнал разъединения с указанием причины
  public:
    static void * FstThread ( void * pthis );
    static void * SecThread ( void * pthis );
    secretarsha_Lena ( sock soket, config* Config ); //конструктор
    ~secretarsha_Lena ( ); //деструктор
    int Auth ( );  // авторизует клиента
    int StartContact ( );  //принммает и обрабатывает данные от клиента
//    void setLogfile ( const string& new_var )   {      m_logfile = new_var;  }
//    string getLogfile ( )   {    return m_logfile;  }
    unsigned int getState_seq ( )   {    return m_ses_state.m_state_seq;  }
    string getClient_name ( )   {    return m_client_name;  } //возвращает имя клиента
    sock getSocket ( )   {    return m_socket;  }
    short Status() {return m_die_status;}
};

#endif // SECRETARSHA_LENA_H
