#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef enum float_class_t {
    PlusZero = 0x00,
    MinusZero = 0x01,
    PlusInf = 0xF0,
    MinusInf = 0xF1,
    PlusRegular = 0x10,
    MinusRegular = 0x11,
    PlusDenormal = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN = 0x30,
    QuietNaN = 0x31,
    Letter = 51,
    Header = 62
} float_class_t;

extern float_class_t classify(double* value_ptr) {
  uint64_t number = *(uint64_t*) (value_ptr);

  bool mant_stat_non_0 = false;
  for (int i = 0; i <= Letter; ++i) {
    if (((number >> i) & 1) == 0) {
      mant_stat_non_0 = true;
      break;
    }
  }

  bool mant_stat_0 = false;
  for (int i = 0; i <= Letter; ++i) {
    if (((number >> i) & 1) == 1) {
      mant_stat_0 = true;
      break;
    }
  }

  bool exp_stat_non_0 = false;
  for (int i = (Letter + 1); i <= Header; ++i) {
    if (((number >> i) & 1) == 0) {
      exp_stat_non_0 = true;
      break;
    }
  }


  bool exp_stat_0 = false;
  for (int i = (Letter + 1); i <= Header; ++i) {
    if (((number >> i) & 1) == 1) {
      exp_stat_0 = true;
      break;
    }
  }

  if (!exp_stat_0 && !mant_stat_0) {
    if ((number >> (Header + 1)) & 1) {
      return MinusZero;
    } else {
      return PlusZero;
    }
  } if (!exp_stat_non_0 && !mant_stat_0) {
    if ((number >> (Header + 1)) & 1) {
      return MinusInf;
    } else {
      return PlusInf;
    }
  } else if (!exp_stat_0 && mant_stat_non_0) {
    if ((number >> (Header + 1)) & 1) {
      return MinusDenormal;
    } else {
      return PlusDenormal;
    }
  } else if (!exp_stat_non_0 && mant_stat_non_0) {
    if ((number >> Letter) & 1) {
      return QuietNaN;
    } else {
      return SignalingNaN;
    }
  } else {
    return ((number >> (Header + 1)) & 1) ? MinusRegular : PlusRegular;
  }
}