#include <stdio.h>
#include "op_codes.h"
#include "state_util.h"
#include "instructions.h"
#include "state.h"

unsigned char TEST_BYTES[] = {0x78, 0xB1, 0xC8, 0x1A, 0x77, 0x13, 0x23, 0x0B, 0x78, 0xB1, 0xC2, 0x03, 0x10, 0xC9};

void update_state(ProcState state) {
  unsigned short pc = get_pc(state);
  OpCode op_code = OP_CODES[get_mem_byte(state, pc)];

  switch (op_code.code) {

    // NOP instruction

    case 0x00:
      // NOP
      break;

    // Carry bit instructions

    case 0x37:
      // STC
      set_carry(state, 1);
      break;
    case 0x3f:
      // CMC
      set_carry(state, !get_carry(state));
      break;

    // Single register instructions

    case 0x04:
      // INR B
      set_reg_b(state, get_reg_b(state) + 1);
      set_parity(state, parity(get_reg_b(state)));
      set_zero(state, zero(get_reg_b(state)));
      set_sign(state, sign(get_reg_b(state)));
      break;

    case 0x05:
      // DCR B
      set_reg_b(state, get_reg_b(state) - 1);
      set_parity(state, parity(get_reg_b(state)));
      set_zero(state, zero(get_reg_b(state)));
      set_sign(state, sign(get_reg_b(state)));
      break;

    case 0x2f:
      // CMA
      set_reg_a(state, complement(get_reg_a(state)));
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
      set_reg_b(state, get_reg_c(state));
      break;
    case 0x42:
      // MOV B,D
      set_reg_b(state, get_reg_d(state));
      break;
    case 0x43:
      // MOV B,E
      set_reg_b(state, get_reg_e(state));
      break;
    case 0x44:
      // MOV B,H
      set_reg_b(state, get_reg_h(state));
      break;
    //....

    case 0x02:
      // STAX B
      set_mem_byte(state, get_reg_pair_b_c(state), get_reg_a(state));
      break;

    case 0x0a:
      // LDAX B
      set_reg_a(state, get_mem_byte(state, get_reg_pair_b_c(state)));
      break;

    // Register or Memory to Accumulator instructions
    case 0x80:
      // ADD B
      addx(&state.reg_b, &state);
      break;

      //...

    case 0x88:
      // ADC B
      adcx(&state.reg_b, &state);
      break;

      //...

    case 0x90:
      // SUB B
      subx(&state.reg_b, &state);
      break;

      //...

    case 0x98:
      // SBB B
      sbbx(&state.reg_b, &state);
      break;

      //...

    case 0xa0:
      // ANA B
      anax(&state.reg_b, &state);
      break;

      //...
    
    case 0xa8:
      // XRA B
      xrax(&state.reg_b, &state);
      break;

      //...

    case 0xb0:
      // ORA B
      orax(&state.reg_b, &state);
      break;

      //...

    case 0xb8:
      // CMP B
      cmpx(&state.reg_b, &state);
      break;

    case 0x76:
      // HLT
      return;
  }

  set_pc(state, pc + op_code.size);
}

int main(int argc, char const *argv[]) {
  ProcState state;

  // // Load Memory
  // copy_to_mem(state, 0, sizeof(TEST_BYTES), TEST_BYTES);

  // // Program Loop
  // while (1) {
  //   update_state(state);
  // }

  // return 0;

  state.reg_a=0b11111111;
  state.reg_b=0b11111111;
  state.reg_c=0b10101010;
  state.reg_d=0x10;
  state.reg_e=0x20;
  state.reg_h=0x30;
  state.reg_l=0x40;
  state.sp=0x100;
  state.carry=0;
  state.aux_carry=0;
  state.zero=0;
  state.parity=0;
  state.sign=0;
  state.mem[0x100] = 0x88;
  state.mem[0x101] = 0x99;
  sphl(&state);
  print_registers(state);
  print_mem(0x100, &state);
}
