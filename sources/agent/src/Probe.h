
#ifndef PROBE_H
#define PROBE_H

#include <string>
#include <vector>
#include "datatypes.h"
#include "pingovator.h"
/*  * class Probe
  * класс для теста одного узла и отсыла данных об нем.
  изменение параметров зонда производится уничтожением старого и созданием нового с тем же идентификатором. для секурности и отсутствия пляок с мутексами.
  */
using namespace std;
class Probe
{
  private:
  unsigned short  timetodie; //флаг завершения потока
  pthread_t m_secthread; //идентификатор потока в котором создается задание
  Pingovator * m_pin; //указатель на пинговатор которому передается задание
  idprobe_t m_IdProbe;  // идентификатор зонда
  probe_status_t m_Status; // статус выставляемый агентом.
  addr_t m_Target;  // адрес проверяемого узла.
  timestamp_t m_Start_Time;  // время начала текущего/последнего теста.
  unsigned long m_Count;  // кол-во запросов в тесте
  unsigned long m_Size;   // размер ICMP_пакета
  unsigned long m_Number;  // номер последнего сгенерированого цикла
  timeoffset_t m_Interval;    // время ожидания между тестами в секундах.
  void Test ( ); //ф-ция создающая цикл и ставящая его в очередь
public:
//  friend void * test_thread(void *);
  /*   * конструктор. с параматрами  по умолчанию */
  Probe (Pingovator * pin=NULL, idprobe_t id_probe=0, probe_status_t state=PS_STOPED, addr_t target=0, int count=0, short size=1,timeoffset_t interval =0);
 ~Probe ( ); //деструктор
 int Start ( ); //изменяет статусна активный
 int Pause ();//изменяет статусна "остановлено"
 idprobe_t GetIdProbe ( ) {return m_IdProbe;}   // возвращает ИД зонда
  int getCount ( )   {    return m_Count;  } //возвращает кол-во дейтаграмм в цикле
  timeoffset_t getInterval ( )   {    return m_Interval;  } //возвращает значение интервала в милисекундах 
  void setStatus(probe_status_t new_var){m_Status = new_var; } //изменяет состояние зонда
  probe_status_t getStatus(){return m_Status; } //возвращает состояние зонда
  addr_t getTarget ( )   {    return m_Target;  } //возвращает адрес теструемого узла
  timestamp_t getStart_Time ( )   {    return m_Start_Time;  } //возвращает время начала последнегоцикла
  int getSize ( )   {    return m_Size;  } //возвращает размер дейтаграмм
  int getNumber(){return m_Number;} //возвращает номер последнего цикла
  static void* test_thread(void *);
};

#endif // PROBE_H
