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
#include <ctime>

#define my_srandom  srandom
#define my_random   random
//#define SEED time(0)
#define SEED 1365439588 //bug2 rotate+rotate
//#define SEED 1365438783 //bug1 rotate+exchange
//#define SEED 1365439384 //good1 rotate+exchange
class RandomNumGen
{
   public:
   //   RandomNumGen() { my_srandom(getpid()); }
      RandomNumGen() { 
		  cout<<"SEED:"<<SEED<<endl; 
		  my_srandom(SEED); 
	  }
      RandomNumGen(unsigned seed) { my_srandom(seed); }
      const double operator() (const double range) const {
         return double(range * (double(my_random()) / INT_MAX));
      }
      const unsigned operator() (const unsigned range) const {
         return unsigned(range * (double(my_random()) / INT_MAX));
      }
};

#endif // RN_GEN_H

