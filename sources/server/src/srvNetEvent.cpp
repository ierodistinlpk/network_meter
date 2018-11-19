#include "srvNetEvent.h"

srvNetEvent::~srvNetEvent ( ) { }

srvNetEvent::srvNetEvent (addr_t address, timestamp_t time, idprobe_t id ,unsigned long num, NetEventType evtype, NetEventClass evclass ):m_IdProbe(id)
{
  m_Adress=ntohl(address);
  m_Time.tv_sec=ntohl(time.tv_sec);
  m_Time.tv_usec=ntohl(time.tv_usec);
  m_EventType=evtype;
  m_EvClass=evclass;
  m_cycle_num=ntohl(num);
}

