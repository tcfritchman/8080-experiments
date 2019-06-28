#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "state.h"

void set_reg_b(ProcState state, unsigned char new_val) {
  state.reg_b = new_val;
}

void set_reg_c(ProcState state, unsigned char new_val) {
  state.reg_c = new_val;
}

void set_reg_d(ProcState state, unsigned char new_val) {
  state.reg_d = new_val;
}

void set_reg_e(ProcState state, unsigned char new_val) {
  state.reg_e = new_val;
}

void set_reg_h(ProcState state, unsigned char new_val) {
  state.reg_h = new_val;
}

void set_reg_l(ProcState state, unsigned char new_val) {
  state.reg_l = new_val;
}

void set_reg_a(ProcState state, unsigned char new_val) {
  state.reg_a = new_val;
}

void set_sp(ProcState state, unsigned short new_val) {
  state.sp = new_val;
}

void set_pc(ProcState state, unsigned short new_val) {
  state.pc = new_val;
}

void set_sign(ProcState state, int new_val) {
  state.sign = new_val;
}

void set_zero(ProcState state, int new_val) {
  state.zero = new_val;
}

void set_parity(ProcState state, int new_val) {
  state.parity = new_val;
}

void set_carry(ProcState state, int new_val) {
  state.carry = new_val;
}

void set_aux_carry(ProcState state, int new_val) {
  state.aux_carry = new_val;
}

void set_mem_byte(ProcState state, unsigned short mem_location, unsigned char new_val) {
  state.mem[mem_location] = new_val;
}

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(ProcState state, unsigned short mem_location,
  unsigned short data_length, unsigned char *data) {
  memcpy(&state.mem[mem_location], data, data_length);
}

unsigned short get_reg_pair_b_c(ProcState state) {
  return state.reg_b | (((unsigned short)state.reg_c) << CHAR_BIT);
}

unsigned short get_reg_pair_d_e(ProcState state) {
  return state.reg_d | (((unsigned short)state.reg_e) << CHAR_BIT);
}

unsigned short get_reg_pair_h_l(ProcState state) {
  return state.reg_h | (((unsigned short)state.reg_l) << CHAR_BIT);
}

unsigned char get_reg_b(ProcState state) {
  return state.reg_b;
}

unsigned char get_reg_c(ProcState state) {
  return state.reg_c;
}

unsigned char get_reg_d(ProcState state) {
  return state.reg_d;
}

unsigned char get_reg_e(ProcState state) {
  return state.reg_e;
}

unsigned char get_reg_h(ProcState state) {
  return state.reg_h;
}

unsigned char get_reg_l(ProcState state) {
  return state.reg_l;
}

unsigned char get_reg_a(ProcState state) {
  return state.reg_a;
}

unsigned short get_sp(ProcState state) {
  return state.sp;
}

unsigned short get_pc(ProcState state) {
  return state.pc;
}

int get_sign(ProcState state) {
  return state.sign;
}

int get_zero(ProcState state) {
  return state.zero;
}

int get_parity(ProcState state) {
  return state.parity;
}

int get_carry(ProcState state) {
  return state.carry;
}

int get_aux_carry(ProcState state) {
  return state.aux_carry;
}

unsigned char get_mem_byte(ProcState state, unsigned short mem_location) {
  return state.mem[mem_location];
}

int parity(unsigned char byte) {
  int set_bit_count = 0;

  for (int i = 0; i < CHAR_BIT; i++) {
    unsigned char tmp = byte >> i;
    if (tmp & 1) {
      set_bit_count++;
    }
  }

  return !(set_bit_count % 2);
}

int sign(unsigned char byte) {
  return byte < 0;
}

int zero(unsigned char byte) {
  return byte == 0;
}

int add_carry(unsigned char byte_1, unsigned char byte_2) {
  if ((byte_1 < 0 && byte_2 >= 0) || (byte_2 < 0 && byte_1 >= 0)) {
    // One of the bytes is negative and the other positive.
    // No chance of carry.
    return 0;
  } else {
    // Both bytes have same sign. Carry is possible and can be determined by
    // whether either byte has the same sign as the sum of the two.
    if (byte_1 < 0) {
      return byte_1 + byte_2 < CHAR_MIN;
    } else {
      return byte_1 + byte_2 > CHAR_MAX;
    }
  }
}

int add_aux_carry(unsigned char byte_1, unsigned char byte_2) {
  // TODO
  return 0;
}

unsigned char complement(unsigned char byte) {
  return byte ^ byte;
}
