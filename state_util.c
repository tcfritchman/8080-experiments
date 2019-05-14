#include <string.h>
#include "state.h"

void set_reg_b(ProcState state, char new_val) {
  state.reg_b = new_val;
}

void set_reg_c(ProcState state, char new_val) {
  state.reg_c = new_val;
}

void set_reg_d(ProcState state, char new_val) {
  state.reg_d = new_val;
}

void set_reg_e(ProcState state, char new_val) {
  state.reg_e = new_val;
}

void set_reg_h(ProcState state, char new_val) {
  state.reg_h = new_val;
}

void set_reg_l(ProcState state, char new_val) {
  state.reg_l = new_val;
}

void set_reg_a(ProcState state, char new_val) {
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

void set_mem_byte(ProcState state, unsigned short mem_location, char new_val) {
  state.mem[mem_location] = new_val;
}

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(ProcState state, unsigned short mem_location,
  unsigned short data_length, char *data) {
  memcpy(&state.mem[mem_location], data, data_length);
}

char get_reg_b(ProcState state) {
  return state.reg_b;
}

char get_reg_c(ProcState state) {
  return state.reg_c;
}

char get_reg_d(ProcState state) {
  return state.reg_d;
}

char get_reg_e(ProcState state) {
  return state.reg_e;
}

char get_reg_h(ProcState state) {
  return state.reg_h;
}

char get_reg_l(ProcState state) {
  return state.reg_l;
}

char get_reg_a(ProcState state) {
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

char get_mem_byte(ProcState state, unsigned short mem_location) {
  return state.mem[mem_location];
}

int parity(char byte) {
  int set_bit_count = 0;

  for (int i = 0; i < 8; i++) {
    char tmp = byte >> i;
    if (tmp & 1) {
      set_bit_count++;
    }
  }

  return !(set_bit_count % 2);
}

int sign(char byte) {
  return byte < 0;
}

int zero(char byte) {
  return byte == 0;
}

char complement(char byte) {
  return byte ^ byte;
}
