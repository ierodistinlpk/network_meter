#include "Cycle.h"
#include "datatypes.h"
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include <time.h>
#include <errno.h>
// Constructors/Destructors
//  
using namespace std;
/*КАНСТРУКТАР */
Cycle::Cycle (idprobe_t idprobe, addr_t target, unsigned short count, unsigned short size, unsigned long number) :
 m_IdProbe(idprobe), m_Target(target),m_Count(count),m_Size(size), m_Number(number)
{
}
Cycle::~Cycle ( ) { }