
#ifndef SECRETARSHA_LENA_H
#define SECRETARSHA_LENA_H

#include string

/**
  * class secretarsha_Lena
  */

class secretarsha_Lena
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  secretarsha_Lena ( );

  /**
   * Empty Destructor
   */
  virtual ~secretarsha_Lena ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return int
   */
  int Auth ( );


  /**
   * задает список проб классу.
   * в name передавать параметр по которому определяется принадлежность зондов агенту
   * на этой линии связи.
   * @return int
   * @param  name
   */
  int setProbelist (string name );


  /**
   * @return int
   */
  int StartContact ( );

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

  string m_logfile;
  unsigned int m_state_seq;
  unsigned char m_SBuf;
  unsigned char m_RBuf;
  string m_client_name;
  list<Probe> m_ProbeList;
  sock m_socket;
  // каждая секретутка подрубается к бд по-своему
  void m_DBconnection;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_logfile
   * @param new_var the new value of m_logfile
   */
  void setLogfile ( string new_var )   {
      m_logfile = new_var;
  }

  /**
   * Get the value of m_logfile
   * @return the value of m_logfile
   */
  string getLogfile ( )   {
    return m_logfile;
  }

  /**
   * Set the value of m_state_seq
   * @param new_var the new value of m_state_seq
   */
  void setState_seq ( unsigned int new_var )   {
      m_state_seq = new_var;
  }

  /**
   * Get the value of m_state_seq
   * @return the value of m_state_seq
   */
  unsigned int getState_seq ( )   {
    return m_state_seq;
  }

  /**
   * Set the value of m_SBuf
   * @param new_var the new value of m_SBuf
   */
  void setSBuf ( unsigned char new_var )   {
      m_SBuf = new_var;
  }

  /**
   * Get the value of m_SBuf
   * @return the value of m_SBuf
   */
  unsigned char getSBuf ( )   {
    return m_SBuf;
  }

  /**
   * Set the value of m_RBuf
   * @param new_var the new value of m_RBuf
   */
  void setRBuf ( unsigned char new_var )   {
      m_RBuf = new_var;
  }

  /**
   * Get the value of m_RBuf
   * @return the value of m_RBuf
   */
  unsigned char getRBuf ( )   {
    return m_RBuf;
  }

  /**
   * Set the value of m_client_name
   * @param new_var the new value of m_client_name
   */
  void setClient_name ( string new_var )   {
      m_client_name = new_var;
  }

  /**
   * Get the value of m_client_name
   * @return the value of m_client_name
   */
  string getClient_name ( )   {
    return m_client_name;
  }

  /**
   * Set the value of m_ProbeList
   * @param new_var the new value of m_ProbeList
   */
  void setProbeList ( list<Probe> new_var )   {
      m_ProbeList = new_var;
  }

  /**
   * Get the value of m_ProbeList
   * @return the value of m_ProbeList
   */
  list<Probe> getProbeList ( )   {
    return m_ProbeList;
  }

  /**
   * Set the value of m_socket
   * @param new_var the new value of m_socket
   */
  void setSocket ( sock new_var )   {
      m_socket = new_var;
  }

  /**
   * Get the value of m_socket
   * @return the value of m_socket
   */
  sock getSocket ( )   {
    return m_socket;
  }

  /**
   * Set the value of m_DBconnection
   * каждая секретутка подрубается к бд по-своему
   * @param new_var the new value of m_DBconnection
   */
  void setDBconnection ( void new_var )   {
      m_DBconnection = new_var;
  }

  /**
   * Get the value of m_DBconnection
   * каждая секретутка подрубается к бд по-своему
   * @return the value of m_DBconnection
   */
  void getDBconnection ( )   {
    return m_DBconnection;
  }
private:



  /**
   * поток с авторизацией и приемкой данных
   */
  void mainthread ( );


  /**
   * поток отправляющий агенту управляющие данные
   * -номера последовательностей всего что можно
   * -приказы создать/убить/изменить зонд
   */
  void ctl_thread ( );

  void initAttributes ( ) ;

};

#endif // SECRETARSHA_LENA_H
