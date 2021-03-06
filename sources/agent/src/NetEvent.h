#ifndef NETEVENT_H
#define NETEVENT_H

#include <string>
#include "datatypes.h"
#include "Post.h"
/**  * class NetEvent
  * описание одного сетевого события  */
using namespace std;
class NetEvent : public Post
{
private:

  addr_t m_Adress;  // IP адрес источника события;
  NetEventType m_EventType;  //          - вид события - errcode или ICMP Code; 
  NetEventClass m_EvClass;  //   - класс события:
  char post_type;
public:
  ~NetEvent ( );
  /*constructor   */
  NetEvent(addr_t addr,  idprobe_t IdProbe, unsigned long cycle_num, NetEventType evtype, NetEventClass evclass);
  int getClassID(){return EVENT;}
  /*   * Get the value of  адрес источника события;   */
  addr_t getAdress ( )   {    return m_Adress;  }
  /*   * Get the value of вид события - errcode или ICMP Code;   */
  NetEventType getEventType ( )   {    return m_EventType;  }
  /*   * Get the value of m_EvClass   */
  NetEventClass getEvClass ( )   {    return m_EvClass;  }
};
#endif // NETEVENT_H
