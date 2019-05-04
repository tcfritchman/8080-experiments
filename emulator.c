#include <stdio.h>
#include "op_codes.h"
#include "program_state.h"

char TEST_BYTES[] = {0x00, 0x00, 0x00, 0x76};

int main(int argc, char const *argv[]) {

  // Load Memory
  copy_to_mem(0, sizeof(TEST_BYTES), TEST_BYTES);

  // Program Loop
  while (1) {

    unsigned short pc = get_pc();
    OpCode op_code = OP_CODES[get_mem_byte(pc)];

    switch (op_code.code) {

      // TODO: OPS other than NOP and HLT

      case 0x00:
        printf("%x\n", 0x00);
        break;
      case 0x76:
        printf("%x\n", 0x76);
        return 0;
    }

    set_pc(pc + op_code.size);
  }
}
