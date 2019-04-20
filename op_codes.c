#include <stdio.h>
#include "op_codes.h"

const OpCode OP_CODES[2] = {
  {
    0x00,
    "NOP",
    1
  },
  {
    0x01,
    "LXI B",
    3
  }
};
