#include <stdio.h>
#include <math.h>

int main (){
  double x, y, z, result;
  x = 2.1;
  y = 4.2;
  z = 10.3;
  
  #ifdef FP_FAST_FMA 
    result = fma(x, y, z);
  #else
    result = (x * y) + z;
  #endif

  printf("(x * y) + z = %f", result);

  return 0;
}