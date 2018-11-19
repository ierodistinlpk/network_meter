#ifndef NETRESULT_H
#define NETRESULT_H

#include "Post.h"
#include <string>
#include <vector>
#include "datatypes.h"
using namespace std;
class NetResult : public Post
{
  private:
  // Private attributes
    unsigned long m_Count; //сколько всего будет
    unsigned long curr_count; //сколько уже заполнено
    vector< node_result_t > m_Result;
public:
  /** Constructor   */
  NetResult (idprobe_t id_probe, unsigned long cyclenum,unsigned long count  );
  NetResult (NetResult& old);
  /**    Destructor   */
  ~NetResult ( );
  int getClassID(){return RESULT;}
  /**   * добавляет следующий rtt или -1 в вектор.
   * возвращает 0 если добавилось,
   * -1 если результатов больше чем Count   */
  int AddResult (long int rtt, unsigned long pos );
  unsigned long int getCount ( )   {    return m_Count;  }
  unsigned long int getCurCount ( )   {    return m_Count-curr_count;  }
  node_result_t getResult (unsigned i )   {    return m_Result[i];  }
};

#endif // NETRESULT_H
