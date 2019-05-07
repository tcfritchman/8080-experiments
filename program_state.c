#include <string.h>
#include <stdio.h>

struct ProcState;

typedef struct ProcState {
  char mem[65536];
  char reg_b;
  char reg_c;
  char reg_d;
  char reg_e;
  char reg_h;
  char reg_l;
  char reg_a;
  int sign;
  int zero;
  int parity;
  int carry;
  int aux_carry;
  unsigned short pc;
  unsigned short sp;
} ProcState;

ProcState state;

void set_reg_b(char new_val) {
  state.reg_b = new_val;
}

void set_reg_c(char new_val) {
  state.reg_c = new_val;
}

void set_reg_d(char new_val) {
  state.reg_d = new_val;
}

void set_reg_e(char new_val) {
  state.reg_e = new_val;
}

void set_reg_h(char new_val) {
  state.reg_h = new_val;
}

void set_reg_l(char new_val) {
  state.reg_l = new_val;
}

void set_reg_a(char new_val) {
  state.reg_a = new_val;
}

void set_sp(unsigned short new_val) {
  state.sp = new_val;
}

void set_pc(unsigned short new_val) {
  state.pc = new_val;
}

void set_sign(int new_val) {
  state.sign = new_val;
}

void set_zero(int new_val) {
  state.zero = new_val;
}

void set_parity(int new_val) {
  state.parity = new_val;
}

void set_carry(int new_val) {
  state.carry = new_val;
}

void set_aux_carry(int new_val) {
  state.aux_carry = new_val;
}

void set_mem_byte(unsigned short mem_location, char new_val) {
  state.mem[mem_location] = new_val;
}

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(unsigned short mem_location,
  unsigned short data_length, char *data) {
  memcpy(&state.mem[mem_location], data, data_length);
}

char get_reg_b() {
  return state.reg_b;
}

char get_reg_c() {
  return state.reg_c;
}

char get_reg_d() {
  return state.reg_d;
}

char get_reg_e() {
  return state.reg_e;
}

char get_reg_h() {
  return state.reg_h;
}

char get_reg_l() {
  return state.reg_l;
}

char get_reg_a() {
  return state.reg_a;
}

unsigned short get_sp() {
  return state.sp;
}

unsigned short get_pc() {
  return state.pc;
}

int get_sign() {
  return state.sign;
}

int get_zero() {
  return state.zero;
}

int get_parity() {
  return state.parity;
}

int get_carry() {
  return state.carry;
}

int get_aux_carry() {
  return state.aux_carry;
}

char get_mem_byte(unsigned short mem_location) {
  return state.mem[mem_location];
}
