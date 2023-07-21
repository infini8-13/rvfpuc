#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "float.h"
#include "minunit.h"
#include "fpu.h"

char *
fsgnjnTest (void)
{
  for (uint32_t i = 0; i < UINT32_MAX; i++)
    {
      static char str[1000];
      const uint32_t a = i;
      // const uint32_t b = i+1;
      const uint32_t c = fsgnjn (a); //for simple testing fsgnjn () is considered with one input.

      mu_assert ((sprintf
      		  (str,
      		   "test of fsgnjn not passed!!\ncase %d\nexpected :%d\nreturned :%d\n",
      		   i,f2i(-(i2f(a))),c),str),f2i(-(i2f(a))) == c);
		 
    }

  return NULL;
}
