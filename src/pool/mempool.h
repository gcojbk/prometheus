#ifndef UTIL_MEMPOOL_H_
#define UTIL_MEMPOOL_H_

#include "singleton.h"
#include <stdio.h>

class MemPool : public Singleton<MemPool>
{
 friend class Singleton<MemPool>;

 private:
    MemPool() {}
    ~MemPool() {}

};


#endif // end of UTIL_MEMPOOL_H_