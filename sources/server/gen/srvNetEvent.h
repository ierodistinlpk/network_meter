
#ifndef SRVNETEVENT_H
#define SRVNETEVENT_H

#include string

/**
  * class srvNetEvent
  * описание одного сетевого события
  * 
  */

class srvNetEvent
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  srvNetEvent ( );

  /**
   * Empty Destructor
   */
  virtual ~srvNetEvent ( );

  // Static Public attributes
  //  

  // Public attributes
  //  

  //          - IP адрес источника события;
  addr_t m_Adress;
  //          - относительное время фиксации события;
  timestamp_t m_Time;
  //          - вид события - errcode или ICMP Code; 
  NetEventType m_EventType;
  //   - класс события:
  //               * Пустая запись (служит для заполнения неиспользуемых элементов массива);
  //               * Ошибка при отправке (при Send вернулся errcode);
  //               * ICMP Destination unreachable (ICMP Type=3);
  //               * ICMP Source Quench (ICMP Type=4);
  //               * ICMP Redirect (ICMP Type=5);
  //               * ICMP Tme Exceeded (ICMP Type=11);
  //               * ICMP Parameter Problem (ICMP Type=12);
  NetEventClass m_EvClass;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of m_Adress
   *          - IP адрес источника события;
   * @param new_var the new value of m_Adress
   */
  void setAdress ( addr_t new_var )   {
      m_Adress = new_var;
  }

  /**
   * Get the value of m_Adress
   *          - IP адрес источника события;
   * @return the value of m_Adress
   */
  addr_t getAdress ( )   {
    return m_Adress;
  }

  /**
   * Set the value of m_Time
   *          - относительное время фиксации события;
   * @param new_var the new value of m_Time
   */
  void setTime ( timestamp_t new_var )   {
      m_Time = new_var;
  }

  /**
   * Get the value of m_Time
   *          - относительное время фиксации события;
   * @return the value of m_Time
   */
  timestamp_t getTime ( )   {
    return m_Time;
  }

  /**
   * Set the value of m_EventType
   *          - вид события - errcode или ICMP Code;
   * @param new_var the new value of m_EventType
   */
  void setEventType ( NetEventType new_var )   {
      m_EventType = new_var;
  }

  /**
   * Get the value of m_EventType
   *          - вид события - errcode или ICMP Code;
   * @return the value of m_EventType
   */
  NetEventType getEventType ( )   {
    return m_EventType;
  }

  /**
   * Set the value of m_EvClass
   *   - класс события:
   *               * Пустая запись (служит для заполнения неиспользуемых элементов
   * массива);
   *               * Ошибка при отправке (при Send вернулся errcode);
   *               * ICMP Destination unreachable (ICMP Type=3);
   *               * ICMP Source Quench (ICMP Type=4);
   *               * ICMP Redirect (ICMP Type=5);
   *               * ICMP Tme Exceeded (ICMP Type=11);
   *               * ICMP Parameter Problem (ICMP Type=12);
   * @param new_var the new value of m_EvClass
   */
  void setEvClass ( NetEventClass new_var )   {
      m_EvClass = new_var;
  }

  /**
   * Get the value of m_EvClass
   *   - класс события:
   *               * Пустая запись (служит для заполнения неиспользуемых элементов
   * массива);
   *               * Ошибка при отправке (при Send вернулся errcode);
   *               * ICMP Destination unreachable (ICMP Type=3);
   *               * ICMP Source Quench (ICMP Type=4);
   *               * ICMP Redirect (ICMP Type=5);
   *               * ICMP Tme Exceeded (ICMP Type=11);
   *               * ICMP Parameter Problem (ICMP Type=12);
   * @return the value of m_EvClass
   */
  NetEventClass getEvClass ( )   {
    return m_EvClass;
  }


  /**
   * @param  address
   * @param  time
   * @param  evtype
   * @param  evclass
   */
  void NetEvent (undef address, undef time, undef evtype, undef evclass );

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:


  void initAttributes ( ) ;

};

#endif // SRVNETEVENT_H
