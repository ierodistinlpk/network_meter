#include "Post.h"
#include <sys/time.h>
#include <iostream>
using namespace std;
unsigned long Post::sequence;
Post::Post (idprobe_t IdProbe, unsigned long Cycle_num):m_IdProbe(IdProbe), m_Cycle_num(Cycle_num),m_seq_num(0) {
  gettimeofday(&m_Time,NULL);
}
