#include "srvProbe.h"

// Constructors/Destructors
srvProbe::srvProbe (idprobe_t id,long interval, long count,addr_t target, short size ):m_IdProbe(id),m_Interval(interval), m_Count(count),m_Target(target),m_Size(size){}

srvProbe::~srvProbe ( ) { }

ProbeState::ProbeState(){}
ProbeState::ProbeState(idprobe_t id, long num,probe_status_t stat ):m_IdProbe(id),m_cycle_num(num),m_state(stat){}
