#include <stdint.h>
#include <math.h>

float_t
fsgnjn (float_t a, float_t b)
{

	return changeSign((getSign(a) ^ getSign(b)), a);
    
}

