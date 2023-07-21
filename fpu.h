//! @note FPU function simulation library
#pragma once
#include <stdint.h>
#include <stdbool.h>

uint32_t
fadd (uint32_t,uint32_t);

uint32_t
fsub (uint32_t,uint32_t);

uint32_t
fmul (uint32_t,uint32_t);

uint32_t
finv (uint32_t in);

#define fdiv(A,B) fmul((A),finv(B))

uint32_t
fsqrt (uint32_t in);

uint32_t
h_i2f (uint32_t);

bool
feq (uint32_t,uint32_t);

bool
flt (uint32_t,uint32_t);

bool
fle (uint32_t,uint32_t);

uint32_t
fsgnjn (uint32_t);
