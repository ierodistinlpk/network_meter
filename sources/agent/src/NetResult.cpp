#include "NetResult.h"
NetResult::NetResult (idprobe_t id_probe, unsigned long cyclenum,unsigned long count  ):Post(id_probe, cyclenum), m_Count(count), curr_count(0),m_Result(m_Count) {
  for(unsigned int i=0;i<m_Count;i++)
    m_Result[i]=0;
}
NetResult::~NetResult ( ) { }
int NetResult::AddResult (long int rtt, unsigned long pos ) 
{
  if(pos>m_Result.size())
  {  cout<<"ОЙ ВСЕ ПЛОХО!!!!!!"<<endl;
    return -1; //возвращает если пинга с таким номером не положено.
  }
  if(m_Result[pos])
    return -2; //возвращает если место уже занято
  m_Result[pos]=rtt;
  curr_count++;
  return 0; //если все успешно
}


