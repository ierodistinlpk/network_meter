#include "NetEvent.h"
#include "datatypes.h"
#include <sys/time.h>
NetEvent::NetEvent (addr_t address,idprobe_t IdProbe, unsigned long cycle_num, NetEventType evtype, NetEventClass evclass ):Post(IdProbe, cycle_num),m_Adress(address),  m_EventType(evtype),m_EvClass(evclass)
{ }
 NetEvent::~NetEvent ( ) { }