#include <stdio.h>
#include <math.h>
#include "fpu.h"
#include "float.h"
uint32_t
fnmadd (uint32_t a, uint32_t b, uint32_t c){
  #ifdef FP_FAST_FMA 
    return fma(a, b, c);
  #else
    return (a * b) + c;
  #endif
  
}