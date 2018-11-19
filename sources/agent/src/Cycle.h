#ifndef CYCLE_H
#define CYCLE_H

#include <string>
#include "datatypes.h"
/**  * class Cycle
  * описание одного цикла пакетов
  */
class Cycle
{
private:
  // Id зонда добавляющего цикл.
  idprobe_t m_IdProbe;
  // адрес цели
  addr_t m_Target;
  // кол-во пакетов
  unsigned short m_Count;
  // размер пакета
  unsigned short m_Size;
  unsigned long m_Number;
  public:
  /* * Empty Constructor   */
    Cycle (idprobe_t idprobe=0, addr_t target=2130706433, unsigned short count=0,unsigned short size=1, unsigned long number=0);
  /*   * Empty Destructor   */
  ~Cycle ( );
  /* возвращает адрес испытуемого узла   */
  addr_t getTarget ( )   { return m_Target;  }
  /* возвращает кол-во пингов в цикле   */
  int getCount ( )   {    return m_Count;  }
  /* возвращяет порядковый номер цикла */
  int getNumber ( )   {    return m_Number;  }
  /*возвращает идентификатор зонда   */
  idprobe_t getIdProbe ( )   {    return m_IdProbe;  }
  /* возвращает размер пакетов  */
  int getSize ( )   {    return m_Size;  }
};

#endif // CYCLE_H
