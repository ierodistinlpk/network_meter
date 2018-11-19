
#ifndef SRVPOSTSTRING_H
#define SRVPOSTSTRING_H

#include <string>
#include <vector>
#include "../../agent_nix/src/datatypes.h"
using namespace std;
/**
  * class srvPostString
  * результат теста в виде понятном серверу.
  */

class srvPostString
{
  public:
 /* Constructor   */
    //все параметры результатов должны быть в сетевом виде.
    srvPostString (idprobe_t id_probe,unsigned long cyclenum,unsigned long count,  unsigned long seq,  timestamp_t time,node_result_t * results);
  /*   * Empty Destructor   */
   ~srvPostString ( );
  // Public attributes
   idprobe_t m_idprobe;
   unsigned long  m_CycleNum;
   unsigned long  m_Count;
   unsigned long seq_num;
   timestamp_t m_Time;
   vector<node_result_t> m_Result;
};

#endif // SRVPOSTSTRING_H
