#include <stdint.h>
#include <float.h>

uint32_t
fsgnj (uint32_t a, uint32_t b)
{
    
	return changeSign(getSign (b), a);
    
}

