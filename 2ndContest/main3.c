#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "inttypes.h"

const uint64_t NUMBERS_LEFT = 1;
const uint64_t NUMBERS_RIGHT = 512;
const uint64_t HEADS_LEFT = 1024;
const uint64_t HEADS_RIGHT = 34359738368ULL;
const uint64_t LETTERS_LEFT = 68719476736ULL;
const uint64_t LETTERS_RIGHT = 2305843009213693952ULL;


uint32_t bijection(uint64_t value) {
  uint32_t func = 0;
  while (value != 0) {
    value >>= (uint32_t) 1;
    func++;
  }
  return (func - 1);
}

uint64_t coding(uint32_t sym) {
  if ((sym <= 57) && (sym >= 48)) {
    return (uint64_t) 1 << (uint64_t) (sym - 48);
  }
  if ((sym <= 90) && (sym >= 65)) {
    return (uint64_t) 1 << (uint64_t) (sym - 55);
  }
  if ((sym <= 122) && (sym >= 97)) {
    return (uint64_t) 1 << (uint64_t) (sym - 61);
  }
  return 0;
}

uint32_t get_value(uint64_t value) {
  if ((value >= NUMBERS_LEFT) && ((value <= NUMBERS_RIGHT))) {
    return bijection(value) + 48;
  }
  if ((value >= HEADS_LEFT) && ((value <= HEADS_RIGHT))) {
    return bijection(value) + 55;
  }
  return bijection(value) + 61;
}

int main() {
  uint64_t final = 0;
  uint64_t current = 0;
  char input;
  while ((input = getchar()) != '\n' && input != EOF) {

    if (input == '^') {
      final ^= current;
      current = (uint64_t) 0;
    } else if (input == '|') {
      final |= current;
      current = (uint64_t) 0;
    } else if (input == '&') {
      final &= current;
      current = (uint64_t) 0;
    } else if (input == '~') {
      final = ~final;
    } else {
      current |= coding((uint64_t) input);
    }
  }

  for (uint64_t i = 0; i < 62; i++) {
    if ((final >> i) & (uint64_t) 1) {
      printf("%c", get_value(((final >> i) & (uint64_t) 1) << i));
    }
  }
  return 0;
}