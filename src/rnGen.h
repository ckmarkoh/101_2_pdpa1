/******************************************************************************
  FileName     [ rnGen.h ]
  PackageName  [ util ]
  Synopsis     [ Random number generator ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2010 LaDs(III), GIEE, NTU, Taiwan ]
******************************************************************************/
#ifndef RN_GEN_H
#define RN_GEN_H

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>  
#include <limits.h>

#define my_srandom  srandom
#define my_random   random

class RandomNumGen
{
   public:
      RandomNumGen() { my_srandom(getpid()); }
      RandomNumGen(unsigned seed) { my_srandom(seed); }
      const double operator() (const double range) const {
         return double(range * (double(my_random()) / INT_MAX));
      }
};

#endif // RN_GEN_H

