#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "inttypes.h"


extern void sum(ITYPE first, ITYPE second, ITYPE *res, int *CF){
  (*res) = 0u;
  ITYPE checker = 0u;
  (*CF) = 0;

  uint64_t bits = sizeof(ITYPE)*8;
  for (uint64_t i=0; i < bits; i++){
    ITYPE first_bit = ((first >> i) & (ITYPE)(1));
    ITYPE second_bit = ((second >> i) & (ITYPE)(1));
    (*res) |= ((first_bit ^ second_bit ^ checker) << i);
    checker = (first_bit & second_bit) | (first_bit & checker) | (second_bit & checker);
  }

  if (checker == 1){
    (*CF) = 1;
  }

}

extern void mul(ITYPE first, ITYPE second, ITYPE* res, int* CF){
  (*res) = 0u;
  ITYPE checker = 0u;
  (*CF) = 0;

  int i = 0;
  while(second != 0){
    ITYPE first_bit = ((first >> i) & (ITYPE)(1));
    ITYPE second_bit = ((second >> i) & (ITYPE)(1));
    if ((second & 0x1) == 0x1){
      sum(first, *res, res, CF);
    }
    second >>= 1;
    first <<= 1;
    checker = (first_bit & second_bit) | (first_bit & checker) | (second_bit & checker);
    i++;
  }

  if (checker == 1){
    (*CF) = 1;
  }

}