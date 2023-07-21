#include <stdint.h>
#include "float.h"

uint32_t
fsgnjx (uint32_t a, uint32_t b)
{

	return changeSign((getSign(a) ^ getSign(b)), a);
    
}

