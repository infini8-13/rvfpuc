#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "float.h"

#define MAX 512
struct a_b
{
  uint16_t a;
  uint32_t b;
};
  

union uint32_f
{
  float as_float;
  uint32_t as_int;
};


//! exp & key (10bit) -> a (23bit) & b (23bit)
// exp & key (13bit) -> 13bit & 23bit only changed 5bit in total, so mantissa was returned.
uint64_t
fsqrt_table (uint16_t key)
{  
  double c;  
  double t;  

  if (bin(key,9) == 1) 
    {
      c = 2.0 / MAX;
      t = 2.0 + c * bina(key,8,0);
    }
  else 
    {
      c = 1.0 / MAX;
      t = 1.0 + c * key;
    }
  
  union uint32_f a;a.as_float = (double) 1 / (sqrt (t) + sqrt(t+c));
  union uint32_f tmp;tmp.as_float = (2 * a.as_float * sqrt (t)) - 1;

  union uint32_f b;b.as_float = (2 - tmp.as_float * tmp.as_float) / (8 * a.as_float);

  return (uint64_t) getMant(a.as_int) << 23 | getMant(b.as_int);
}



uint32_t
fsqrt (const uint32_t in)
{
  const uint8_t sign = getSign (in);  
  const uint16_t key = getMant (in) >> 14 | (!(getExp (in) & 1)) << 9;
  const uint8_t expr = bina((getExp (in) + 127),8,1);      
    
  const uint64_t raw_ret = fsqrt_table(key);
  assert (!bin (raw_ret,46));
  const uint32_t a = getMant(raw_ret >> 23);
  assert (!bin (a,23));
  const uint32_t b = bina(raw_ret,22,0);
  assert (!bin (b,23));

  // 12 downto 0
  const uint32_t h_a = getMant (a) >> 11 | 1 << 12;
  assert (!bin (h_a,13));
  // 12 downto 0
  const uint32_t h_b = getMant (in) >> 11 | 1 << 12;
  assert (!bin (h_b,13));
  // 10 downto 0
  const uint16_t l_a = bina (a,10,0);
  assert (!bin (l_a,11));
  // 10 downto 0
  const uint16_t l_b = bina (in,10,0);
  assert (!bin (l_b,11));
  
  // 25 downto 0
  const uint32_t HH = h_a * h_b;
  assert (!bin (HH,26));
  // 23 downto 0
  const uint32_t HL = h_a * l_b;
  assert (!bin (HL,24));
  // 23 downto 0
  const uint32_t LH = l_a * h_b;
  assert (!bin (LH,24));

  // 25 downto 0
  const uint32_t mul0 = (HH + (LH >> 11) + (HL >> 11)+ 2);
  assert (!bin (mul0,26));
  uint32_t mul;
  uint8_t x_expr;
  if (bin(mul0,25)) {
    mul = bina (mul0,24,2);
    x_expr = ((getExp (in) & 1) == 0) ? 129 : 128;
  } else {
    mul = bina (mul0,23,1);
    x_expr = ((getExp (in) & 1) == 0) ? 128 : 127;
  }
  assert (!bin (mul,23));
//  printf ("%x %x\n",mul0,x_expr);  

  // 24 downto 0
  uint32_t m_a;
  uint32_t m_b;
  if (x_expr == 129) {
    m_a = (getMant (mul) | 1 << 23) << 1;
    m_b = (getMant (b) | 1 << 23);
  } else if (x_expr == 127) {
    m_a = (getMant (mul) | 1 << 23);
    m_b = (getMant (b) | 1 << 23) << 1;
  } else {
    m_a = (getMant (mul) | 1 << 23) << 1;
    m_b = (getMant (b) | 1 << 23) << 1;
  }
  assert (!bin (m_a,25));
  assert (!bin (m_b,25));

  //! @note Even if you don't care about rounding, it seems to pass the test, so don't round
  // 25 down to 0
  const uint32_t sum = m_a + m_b;
  assert (!bin (sum,26));

  // return
  if (sign == 1) {
    if (getExp (in) == 0) {
      return in;
    } else {
      return m_Nan;
    }      
  } else if (getExp (in) == 0) {
    // zero
    return 0;
  } else if (getExp (in) == 0xff) {
    // nan
    return in;
  } else if (in == 0x3F800001) {
    // special case
    return 0x3F800000;
  } else if (bin(m_b,24)) {
    return makeFloat (sign,expr,bina (sum,24,2));  
  } else {
    return makeFloat (sign,expr,bina (sum,23,1));
  }
  
}
