#ifndef POST_H
#define POST_H

#include <string>
#include "datatypes.h"
#include <vector>
using namespace std;
class Post
{
  private:
    idprobe_t m_IdProbe; //идентификатор зонда
    unsigned long m_Cycle_num; //номер цикла
    timestamp_t m_Time; //время создания
    static unsigned long sequence; //счетчик номеров
    unsigned long m_seq_num; //номер текущего объекта
public:
  Post (idprobe_t IdProbe, unsigned long Cycle_num); //конструктор
  Post (Post& old); //конструктор копирования
  Post& operator=(Post& old); //конструктор копирования
  idprobe_t getIdProbe ( )   { return m_IdProbe;  } //возвращает идентификатор зонда
  unsigned long getCycleNum ( )   { return m_Cycle_num;  } //возвращает номер цикла
  timestamp_t getTime ( )   { return m_Time;  } //возвращает структуру со временем создания
  unsigned long getSeq ( )   { return m_seq_num;  } //возвращает номер в последвательности
  unsigned long LetNum ( )   { sequence++;
    return m_seq_num=sequence; } //возвращает номер в последвательности
  virtual ~Post ( ){} //деструктор
  virtual int getClassID()=0; //служит для определения типа производного объекта
};

#endif // POST_H
