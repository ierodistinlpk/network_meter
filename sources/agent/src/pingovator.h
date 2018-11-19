
#ifndef PINGOVATOR_H
#define PINGOVATOR_H

#include <string>
#include <vector>
#include <list>
#include<map>
#include "Cycle.h"
#include "datatypes.h"
#include "NetResult.h"
#include "NetEvent.h"
/**  * class Pingovator
  * обрабатывает очередь циклов.
  * выполняет цикл как только он поступает в очередь.
  * при создании обекта инициализирует сокет и очередь циклов  */
using namespace std;
class Agent; //во избежание зацикливаний заголовков
class Pingovator
{
  private:
    list<Cycle> m_Query; // список циклов для исполнения
    map<map_key,NetResult*> m_ResMap; //карта результатов ожидающих заполнения.
    pthread_t m_f_thread; //поток отправляющий запросы
    pthread_t m_s_thread;//поток принимающий запросы
    pthread_mutex_t ProbeMutex; // мьютекс на работу с очередью.
    unsigned short m_time_to_die; //флаг остановки потоков
    sock m_socket; //сырой сокет для отпраки/приема запросов
    unsigned char m_RBuf[RAWBUF_SIZE]; //буфер приема сообщений
    unsigned char m_SBuf[RAWBUF_SIZE]; //буфер отправки сообщений
    Agent * comandor; //указатель на экземпляр агента которому возвращать результаты
    void ExecCycle ();  // поток выполняющий циклы
    void initReadSocket ( ); //поток читающий данные из сокета
public:
  Pingovator ( Agent* comandor ); //конструктор
 ~Pingovator ( ); //деструктор
 void AddCycle (Cycle &cycle );   /*   * добавляет цикл в очередь.   */
  int getSocket(){return m_socket;} //возвращает идентификатор сокета.
  static void * FstThread (void * pthis );
  static void * SecThread (void * pthis );
};
#endif // PINGOVATOR_H
