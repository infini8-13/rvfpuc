#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "float.h"
#include "minunit.h"
#include "fpu.h"

bool
feqAdapter (float a,float b)
{
  return feq (f2i (a),f2i (b));  
}


char *
feqTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = frand (), b = frand ();
      //not for denormalised numbers
      if (fpclassify (a) != FP_NORMAL || fpclassify (b) != FP_NORMAL)
	continue;
      bool c = feqAdapter (a, b);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of feq not passed!!\nexpected :%d\nreturned :%d\n",
		   a == b, c), str), (a == b) == c);      
    }

  return NULL;
}
