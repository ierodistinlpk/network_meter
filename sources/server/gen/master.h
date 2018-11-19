
#ifndef MASTER_H
#define MASTER_H

#include string

/**
  * class master
  */

class master
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  master ( );

  /**
   * Empty Destructor
   */
  virtual ~master ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  filename
   */
  void readConfig (string filename );


  /**
   */
  void SetBigList ( );

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

  list<secretarsha_Lena> m_secretarylist;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_secretarylist
   * @param new_var the new value of m_secretarylist
   */
  void setSecretarylist ( list<secretarsha_Lena> new_var )   {
      m_secretarylist = new_var;
  }

  /**
   * Get the value of m_secretarylist
   * @return the value of m_secretarylist
   */
  list<secretarsha_Lena> getSecretarylist ( )   {
    return m_secretarylist;
  }
private:


  void initAttributes ( ) ;

};

#endif // MASTER_H
