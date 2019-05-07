#include <stdio.h>
#include "op_codes.h"
#include "state_util.h"
#include "state.h"

char TEST_BYTES[] = {0x78, 0xB1, 0xC8, 0x1A, 0x77, 0x13, 0x23, 0x0B, 0x78, 0xB1, 0xC2, 0x03, 0x10, 0xC9};

int main(int argc, char const *argv[]) {

  ProcState state;

  // Load Memory
  copy_to_mem(state, 0, sizeof(TEST_BYTES), TEST_BYTES);

  // Program Loop
  while (1) {

    unsigned short pc = get_pc(state);
    OpCode op_code = OP_CODES[get_mem_byte(state, pc)];

    switch (op_code.code) {
      case 0x00:
        // NOP
        break;

      //....
      case 0x40:
        // NOP
        break;
      case 0x41:
        set_reg_b(state, get_reg_c(state));
        break;
      case 0x42:
        set_reg_b(state, get_reg_d(state));
        break;
      //....
      case 0x76:
        return 0;
    }

    set_pc(state, pc + op_code.size);
  }
}
