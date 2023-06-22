#include <stdint.h>
#include <float.h>
#include <math.h>

float_t
fneg (float_t a, float_t b)
{
	return changeSign(getSign(b), a);
    
}

