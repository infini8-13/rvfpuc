#include <stdint.h>
#include <float.h>
#include <math.h>

float_t
fsgnjn (float_t a, float_t b)
{
    switch (getSign (b)) {
    case 0:
	return changeSign(1, a);
    default:
	return changeSign(0, a);
    }
    
}

