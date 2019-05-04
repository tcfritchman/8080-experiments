#include <string.h>
#include <stdio.h>

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
//TODO: IO

void set_reg_b(char new_val) {
  reg_b = new_val;
}

void set_reg_c(char new_val) {
  reg_c = new_val;
}

void set_reg_d(char new_val) {
  reg_d = new_val;
}

void set_reg_e(char new_val) {
  reg_e = new_val;
}

void set_reg_h(char new_val) {
  reg_h = new_val;
}

void set_reg_l(char new_val) {
  reg_l = new_val;
}

void set_reg_a(char new_val) {
  reg_a = new_val;
}

void set_sp(unsigned short new_val) {
  sp = new_val;
}

void set_pc(unsigned short new_val) {
  pc = new_val;
}

void set_sign(int new_val) {
  sign = new_val;
}

void set_zero(int new_val) {
  zero = new_val;
}

void set_parity(int new_val) {
  parity = new_val;
}

void set_carry(int new_val) {
  carry = new_val;
}

void set_aux_carry(int new_val) {
  aux_carry = new_val;
}

void set_mem_byte(unsigned short mem_location, char new_val) {
  mem[mem_location] = new_val;
}

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(unsigned short mem_location,
  unsigned short data_length, char *data) {
  memcpy(&mem[mem_location], data, data_length);
}

char get_reg_b() {
  return reg_b;
}

char get_reg_c() {
  return reg_c;
}

char get_reg_d() {
  return reg_d;
}

char get_reg_e() {
  return reg_e;
}

char get_reg_h() {
  return reg_h;
}

char get_reg_l() {
  return reg_l;
}

char get_reg_a() {
  return reg_a;
}

unsigned short get_sp() {
  return sp;
}

unsigned short get_pc() {
  return pc;
}

int get_sign() {
  return sign;
}

int get_zero() {
  return zero;
}

int get_parity() {
  return parity;
}

int get_carry() {
  return carry;
}

int get_aux_carry() {
  return aux_carry;
}

char get_mem_byte(unsigned short mem_location) {
  return mem[mem_location];
}
