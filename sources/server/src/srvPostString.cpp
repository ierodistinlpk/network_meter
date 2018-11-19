#include "srvPostString.h"
#include "../../agent_nix/src/datatypes.h"

#include <sys/types.h>

// Constructors/Destructors
//  


srvPostString::~srvPostString ()
{
  m_Result.clear();
}

/* конструктор со всеми параметрами */
srvPostString::srvPostString (idprobe_t id_probe,unsigned long cyclenum,unsigned long count,unsigned long seq,   timestamp_t time, node_result_t * results ): m_idprobe(id_probe){

  m_CycleNum=ntohl(cyclenum);
  m_Count=ntohl(count);
  seq_num=ntohl(seq);
  m_Time.tv_sec=ntohl(time.tv_sec);
  m_Time.tv_usec=ntohl(time.tv_usec);
  m_Result.resize(m_Count);
for(unsigned i=0;i<count;i++)
  m_Result[i]=ntohl(results[i]);
}

