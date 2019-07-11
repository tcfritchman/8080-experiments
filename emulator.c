#include <stdio.h>
#include "op_codes.h"
#include "state_util.h"
#include "instructions.h"
#include "state.h"

unsigned char TEST_BYTES[] = {0x78, 0xB1, 0xC8, 0x1A, 0x77, 0x13, 0x23, 0x0B, 0x78, 0xB1, 0xC2, 0x03, 0x10, 0xC9};

void update_state(ProcState *state) {
  unsigned short pc = state->pc;
  OpCode op_code = OP_CODES[state->mem[pc]];

  switch (op_code.code) {

    // NOP instruction

    case 0x00:
      // NOP
      break;

    // Carry bit instructions

    case 0x37:
      // STC
      break;
    case 0x3f:
      // CMC
      break;

    // Single register instructions

    case 0x04:
      // INR B
      break;

    case 0x05:
      // DCR B
      break;

    case 0x2f:
      // CMA
      break;

    case 0x27:
      // DAA
      // TODO
      break;

    // Data Transfer instructions

    //....
    case 0x40:
      // MOV B,B (NOP)
      break;
    case 0x41:
      // MOV B,C
      break;
    case 0x42:
      // MOV B,D
      break;
    case 0x43:
      // MOV B,E
      break;
    case 0x44:
      // MOV B,H
      break;
    //....

    case 0x02:
      // STAX B
      break;

    case 0x0a:
      // LDAX B
      break;

    // Register or Memory to Accumulator instructions
    case 0x80:
      // ADD B
      break;

      //...

    case 0x88:
      // ADC B
      break;

      //...

    case 0x90:
      // SUB B
      break;

      //...

    case 0x98:
      // SBB B
      break;

      //...

    case 0xa0:
      // ANA B
      break;

      //...
    
    case 0xa8:
      // XRA B
      break;

      //...

    case 0xb0:
      // ORA B
      break;

      //...

    case 0xb8:
      // CMP B
      break;

    case 0x76:
      // HLT
      return;
  }

  state->pc += op_code.size;
}

void init_state(ProcState *state) {
  state->reg_a=0x52;
  state->reg_b=0b11111111;
  state->reg_c=0b10101010;
  state->reg_d=0x10;
  state->reg_e=0x20;
  state->reg_h=0x30;
  state->reg_l=0x40;
  state->pc=0x777;
  state->sp=0x100;
  state->carry=0;
  state->aux_carry=0;
  state->zero=0;
  state->parity=0;
  state->sign=0;
  state->mem[0x100] = 0x88;
  state->mem[0x101] = 0x99;
}

int main(int argc, char const *argv[]) {
  ProcState state;
  init_state(&state);

  // Load Memory
  copy_to_mem(state, 0, sizeof(TEST_BYTES), TEST_BYTES);

  // Program Loop
  while (1) {
    update_state(&state);
  }

  return 0;
}
