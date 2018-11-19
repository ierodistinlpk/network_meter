
#ifndef SRVPOSTSTRING_H
#define SRVPOSTSTRING_H

#include string

/**
  * class srvPostString
  * результат теста в виде понятном серверу.
  */

class srvPostString
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  srvPostString ( );

  /**
   * Empty Destructor
   */
  virtual ~srvPostString ( );

  // Static Public attributes
  //  

  // Public attributes
  //  

  idprobe_t m_idprobe;
  unsigned long m_CycleNum;
  unsigned long m_Count;
  // должен задаваться не вектором, а динамическим массивом во избежание бардака при передаче структуры вектора по сети
  list<unsigned long> m_Result;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of m_idprobe
   * @param new_var the new value of m_idprobe
   */
  void setIdprobe ( idprobe_t new_var )   {
      m_idprobe = new_var;
  }

  /**
   * Get the value of m_idprobe
   * @return the value of m_idprobe
   */
  idprobe_t getIdprobe ( )   {
    return m_idprobe;
  }

  /**
   * Set the value of m_CycleNum
   * @param new_var the new value of m_CycleNum
   */
  void setCycleNum ( unsigned long new_var )   {
      m_CycleNum = new_var;
  }

  /**
   * Get the value of m_CycleNum
   * @return the value of m_CycleNum
   */
  unsigned long getCycleNum ( )   {
    return m_CycleNum;
  }

  /**
   * Set the value of m_Count
   * @param new_var the new value of m_Count
   */
  void setCount ( unsigned long new_var )   {
      m_Count = new_var;
  }

  /**
   * Get the value of m_Count
   * @return the value of m_Count
   */
  unsigned long getCount ( )   {
    return m_Count;
  }

  /**
   * Set the value of m_Result
   * должен задаваться не вектором, а динамическим массивом во избежание бардака при
   * передаче структуры вектора по сети
   * @param new_var the new value of m_Result
   */
  void setResult ( list<unsigned long> new_var )   {
      m_Result = new_var;
  }

  /**
   * Get the value of m_Result
   * должен задаваться не вектором, а динамическим массивом во избежание бардака при
   * передаче структуры вектора по сети
   * @return the value of m_Result
   */
  list<unsigned long> getResult ( )   {
    return m_Result;
  }


  /**
   * конструктор со всеми параметрами
   * @param  id_probe
   * @param  cyclenum
   * @param  count
   * @param  results
   */
  void PostString (undef id_probe, undef cyclenum, undef count, unsigned int * results );

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

#endif // SRVPOSTSTRING_H
