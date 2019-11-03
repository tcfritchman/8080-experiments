#include <stdio.h>
#include "state.h"

unsigned char init_input_func_stub() {
  printf("WARN: Attempt to read data from unmapped input device\n");
  return 0;
}

void init_output_func_stub(unsigned char data) {
  printf("WARN: Attempt to write data to unmapped output device\n");
}

void init_state(State8080 *state) {
  state->reg_a=0x00;
  state->reg_b=0x00;
  state->reg_c=0x00;
  state->reg_d=0x00;
  state->reg_e=0x00;
  state->reg_h=0x00;
  state->reg_l=0x00;
  state->pc=0x0000;
  state->sp=0x0000;
  state->carry=0;
  state->aux_carry=0;
  state->zero=0;
  state->parity=0;
  state->sign=0;
  state->inte=1;
  state->is_interrupted=0;
  for (int i = 0; i < 256; i++) {
    // Initialize the input and output handlers with a stub which logs an error message
    state->inputs[i] = init_input_func_stub;
    state->outputs[i] = init_output_func_stub;
  }
}

int parity(unsigned char byte) {
  int set_bit_count = 0;

  for (int i = 0; i < BYTE_SIZE_8080; i++) {
    unsigned char tmp = byte >> i;
    if (tmp & 1) {
      set_bit_count++;
    }
  }

  return !(set_bit_count % 2);
}

int sign(unsigned char byte) {
  return (byte & 0x80) >> 7;
}

int zero(unsigned char byte) {
  return byte == 0;
}

void print_registers_compact(State8080 *state) {
  char sign = state->sign ? 'S' : '_';
  char parity = state->parity ? 'P' : '_';
  char zero = state->zero ? 'Z' : '_';
  char carry = state->carry ? 'C' : '_';
  char aux_carry = state->aux_carry ? 'A' : '_';
  printf("b:%02x c:%02x d:%02x e:%02x h:%02x l:%02x a:%02x sp:%04x %c%c%c%c%c",
    state->reg_b,
    state->reg_c,
    state->reg_d,
    state->reg_e,
    state->reg_h,
    state->reg_l,
    state->reg_a,
    state->sp,
    sign,
    parity,
    zero,
    carry,
    aux_carry);
}

void print_registers(State8080 state) {
  printf("\
BC: 0x%02x 0x%02x\n\
DE: 0x%02x 0x%02x\n\
HL: 0x%02x 0x%02x\n\
ACC: 0x%02x\n\
SIGN: %d\n\
ZERO: %d\n\
PARITY: %d\n\
CARRY: %d\n\
AUX_CARRY: %d\n\
SP: 0x%04x\n\
PC: 0x%04x\n",
  state.reg_b,
  state.reg_c,
  state.reg_d,
  state.reg_e,
  state.reg_h,
  state.reg_l,
  state.reg_a,
  state.sign,
  state.zero,
  state.parity,
  state.carry,
  state.aux_carry,
  state.sp,
  state.pc);
}

void print_mem_r(unsigned short mem_addr, unsigned short pre_bytes, unsigned short post_bytes, State8080 *state) {
  for (int i = mem_addr - pre_bytes; i < mem_addr + post_bytes; i++) {
    printf("Ox%04x: 0x%02x\n", i, state->mem[i]);
  }
}

void print_mem_c(unsigned short mem_addr, unsigned short post_bytes, State8080 *state) {
  print_mem_r(mem_addr, 0, post_bytes, state);
}

void print_mem(unsigned short mem_addr, State8080 *state) {
  print_mem_r(mem_addr, 0, 8, state);
}

unsigned char *get_mem_byte(State8080 *state) {
  unsigned short mem_addr = (state->reg_h << 8) ^ state->reg_l;
  return &state->mem[mem_addr];
}
