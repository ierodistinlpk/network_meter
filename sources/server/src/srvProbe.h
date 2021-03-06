#ifndef SRVPROBE_H
#define SRVPROBE_H

#include <string>
#include "../../agent_nix/src/datatypes.h"
/**  * class srvProbe
  * класс для теста одного узла и отсыла данных об нем.  */

class srvProbe
{
private:
  idprobe_t m_IdProbe;
    // время ожидания между тестами в секундах.
  long m_Interval;
  // кол-во пингов в тесте
  long m_Count; //или кол-во пройденых циклов - по смыслу
  // адрес проверяемого данным зондом.
  addr_t m_Target;
  // размер пинга
  short m_Size;
public:
    /*   * Empty Constructor   */
  srvProbe (idprobe_t id,long interval, long count,addr_t target, short size );
    /*   * Empty Destructor   */
    ~srvProbe ( );
  /*   * Set the value of кол-во пингов в тесте   */
  void setCount ( long new_var )   {      m_Count = new_var;  }
  /*   Get the value of кол-во пингов в тесте  */
  long getCount ( )   {    return m_Count;  }
  /*   * Set the value of время ожидания между тестами в секундах.*/
  void setInterval ( long new_var )   {      m_Interval = new_var;  }
  /*   * Get the value of время ожидания между тестами в секундах.   */
  long getInterval ( )   {    return m_Interval;  }
  /*   * Set the value of  адрес проверяемого данным зондом.*/
  void setTarget ( addr_t new_var )   {      m_Target = new_var;  }
  /*   * Get the value of m_Target    */
  addr_t getTarget ( )   {    return m_Target;  }
  /*   * Set the value of  размер пинга   */
  void setSize ( short new_var )   {      m_Size = new_var;  }
  /*   * Get the value of размер пинга   */
  short getSize ( )   {    return m_Size;  }
  /*   * Set the value of idprobe   */
  void setIdProbe ( idprobe_t new_var )   {      m_IdProbe = new_var;  }
  /*   * Get the value of m_IdProbe    */
  idprobe_t getIdProbe ( )   {    return m_IdProbe;  }
};

class ProbeState
{
  private:
    idprobe_t m_IdProbe;
    // время ожидания между тестами в секундах.
    long m_cycle_num;
  // статус
    probe_status_t m_state;
  public:
    ProbeState();
    ProbeState(idprobe_t id, long num,probe_status_t stat );
    idprobe_t getIdProbe ( )   {    return m_IdProbe;  }
};
#endif // SRVPROBE_H
