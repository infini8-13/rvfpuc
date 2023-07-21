#!/bin/bash

tests="fmul fadd fsub floor i2f fsqrt feq flt fsgnjn"

for a in $tests; do
    ./${a}_test > ../${a}.dat
done
