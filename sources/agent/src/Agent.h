/************************************************************************
                        Agent.h.h - Copyright iero

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/share/apps/umbrello/headings/heading.h

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
The original location of this file is /media/s2/univer/diplomko/agent_nix/Agent.h
**************************************************************************/

#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>
#include <list>
#include <sys/socket.h>
#include <sys/time.h>
#include "Probe.h"
#include "Post.h"
#include "pingovator.h"
#include "datatypes.h"
using namespace std;
/**  * class Agent  * основной класс агента.  */
class Agent
{
  private:
    pthread_mutex_t send_mut; //мютекс на сокет общения с сервером
    pthread_t m_r_thread; //поток отправки результатов
    pthread_mutex_t m_query_mutex; //мютекс очереди результатов
    unsigned short m_time_to_die; //флаг для сигнала завершения второму потоку
  //Данные идентификации и авторизации
    string m_Name;   // условное имя агента
    string m_SrvName; // адрес сервера в виде строки
    adress_t m_Address; //адрес сервера в сетевом виде
    string m_secret_adres; //путевое имя файла с паролем
    string m_secret; //строка для пароля
    unsigned short m_Port; //порт подключения
    sock m_Soket; //сокет связи с сервером.
    unsigned long m_next_result; //номер ожидаемого сервером сообщения
    unsigned long m_cur_post; //последний отправленный результат
    timestamp_t last_comm_time; //время последней команды
    timestamp_t last_request_time; //время последнего запроса сотояния
    long m_comm_seq; //номер последней команды
    long long m_SessionId; //идентификатор сеанса связи
    // буферы приема и отправления .
    msg_header m_HRBuf; //заголовок буфера приема
    msg_header m_HSBuf; //заголовок буфера отправки
    unsigned char m_RBuf[DBUF_SIZE]; //буфер приема
    unsigned char m_SBuf[DBUF_SIZE]; //буфер отправки
    //указатели разных типов на начало буфера
    //на прием
    intro_s * pintro; //для Intro
    sesstart_s * psesstart; //для Session Start
    disconnect_s * pdisconnect; //для Disconnect
    getclstate_s * pgetclstate; //для get Client State
    setprobe_s * psetprobe; //для Set Probe
    dataack_s * pdataack; //для Data Ack
    // на отправление
    login_s * plogin; //для Login
    clientstate_s * pclientstate; //для Client State
    proberesult_s * pproberesult; //для Probe Result
    eventlog_s * peventlog; //для Event Log
    cldisconnect_s * pclientdisconnect; //для Client Disconnect
    /////////////////////////////////////////////////////////////////////////////////
    list<Post*> m_PostList;  // очередь результатов для отправки на сервер.
    list<Probe*> m_ProbeList; //список зондов
    Pingovator * m_pinger; //пинговатор принадлежащий агенту.
    //внутренние методы
    // 3 метода возвращают отрцательный пользовательский код или положительный errno
    int Connect ( );   //соединяется с сервером по tcp.
    int Auth(); //авторизуется на сервере. возвращает code принятый от сервера
    int StartQuest ( );     //переводит в состояние ожидания приказов от сервера
    void SendResult ( );  //запускает нить передачи результатов
    void KillSec(); //уничтожает второй поток с ожиданием звершения.
    int SendBuf(); //отправляет уже заполненый буфер с заголовком на сервер
public:
  Agent ( ); //конструктор по умолчанию
  ~Agent ( ); //деструктор
  int ReadConfig(string filename); //читает конфигурационный файл
  int StartWork ();   // запускает  работу агента
  void AddResult (Post* result );   //  добавляет результат в очередь 
  string getName ( )   {    return m_Name;  } //    возвращает условное имя агента 
  static void * SecThread (void * pthis ); //стандартный механизм запуска потоков в классе
};

#endif // AGENT_H
