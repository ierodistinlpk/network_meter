#include "Probe.h"
#include "Cycle.h"
#include <pthread.h>
#include <time.h>
#include <iostream>
/*конструктор. */
Probe::Probe (Pingovator * pin, idprobe_t id_probe, probe_status_t state, addr_t target, int count, short size,timeoffset_t interval ):timetodie(0), m_pin(pin),m_IdProbe(id_probe), m_Status(state), m_Target(target), m_Count(count), m_Size(size), m_Number(0)
{
     m_Interval=interval;
   if ((pthread_create(&m_secthread, NULL, &Probe::test_thread,this))!=0)//в этом треде  цикл
   m_Status=PS_BROKEN; //статус "паламато" если тред не удалосьсоздать
}
Probe::~Probe ( ) {
  timetodie=1;
  pthread_join(m_secthread,NULL);
}
/* * запускает тест при старте агента/выходе с паузы */
int Probe::Start ( ) {
  m_Status=PS_WAITING;
return 0;
}
/* * приостанавливает процесс по окончанию теста или расчета его результата. * при time=0 - до вызова Start */
int Probe::Pause () {
  m_Status=PS_STOPED;
  return 0;
}
/* * внутренняя процедура, создающая цикл и ставящая его в очередь */
void Probe::Test ( ) 
{
  while(!timetodie)
  {
    if(m_Status!=PS_STOPED)
    {
      m_Number++;
      Cycle cycle(m_IdProbe,m_Target,m_Count,m_Size,m_Number);
      m_pin->AddCycle(cycle); //ставим в очередь
    }
    for(int i=0;i<m_Interval;i++)
    {
      usleep(1000);
      if (timetodie)
        return;
    }
  }
}
void* Probe::test_thread(void * ths) //в этом треде созданная проба запускается на выполнение
{
  Probe * curprobe = (Probe*)ths;
  curprobe->Test();
  return NULL;
}