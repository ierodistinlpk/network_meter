
#ifndef SRVPROBE_H
#define SRVPROBE_H

#include string

/**
  * class srvProbe
  * класс для теста одного узла и отсыла данных об нем.
  */

class srvProbe
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  srvProbe ( );

  /**
   * Empty Destructor
   */
  virtual ~srvProbe ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


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

  // кол-во пингов в тесте
  long m_Count;
  // время ожидания между тестами в секундах.
  long m_Interval;
  // адрес проверяемого данным зондом.
  addr_t m_Target;
  // размер пинга
  short m_Size;
  idprobe_t m_IdProbe;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_Count
   * кол-во пингов в тесте
   * @param new_var the new value of m_Count
   */
  void setCount ( long new_var )   {
      m_Count = new_var;
  }

  /**
   * Get the value of m_Count
   * кол-во пингов в тесте
   * @return the value of m_Count
   */
  long getCount ( )   {
    return m_Count;
  }

  /**
   * Set the value of m_Interval
   * время ожидания между тестами в секундах.
   * @param new_var the new value of m_Interval
   */
  void setInterval ( long new_var )   {
      m_Interval = new_var;
  }

  /**
   * Get the value of m_Interval
   * время ожидания между тестами в секундах.
   * @return the value of m_Interval
   */
  long getInterval ( )   {
    return m_Interval;
  }

  /**
   * Set the value of m_Target
   * адрес проверяемого данным зондом.
   * @param new_var the new value of m_Target
   */
  void setTarget ( addr_t new_var )   {
      m_Target = new_var;
  }

  /**
   * Get the value of m_Target
   * адрес проверяемого данным зондом.
   * @return the value of m_Target
   */
  addr_t getTarget ( )   {
    return m_Target;
  }

  /**
   * Set the value of m_Size
   * размер пинга
   * @param new_var the new value of m_Size
   */
  void setSize ( short new_var )   {
      m_Size = new_var;
  }

  /**
   * Get the value of m_Size
   * размер пинга
   * @return the value of m_Size
   */
  short getSize ( )   {
    return m_Size;
  }

  /**
   * Set the value of m_IdProbe
   * @param new_var the new value of m_IdProbe
   */
  void setIdProbe ( idprobe_t new_var )   {
      m_IdProbe = new_var;
  }

  /**
   * Get the value of m_IdProbe
   * @return the value of m_IdProbe
   */
  idprobe_t getIdProbe ( )   {
    return m_IdProbe;
  }
private:


  void initAttributes ( ) ;

};

#endif // SRVPROBE_H
