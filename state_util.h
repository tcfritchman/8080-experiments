#include "state.h"

void set_reg_b(ProcState state, unsigned char new_val);

void set_reg_c(ProcState state, unsigned char new_val);

void set_reg_d(ProcState state, unsigned char new_val);

void set_reg_e(ProcState state, unsigned char new_val);

void set_reg_h(ProcState state, unsigned char new_val);

void set_reg_l(ProcState state, unsigned char new_val);

void set_reg_a(ProcState state, unsigned char new_val);

void set_sp(ProcState state, unsigned short new_val);

void set_pc(ProcState state, unsigned short new_val);

void set_sign(ProcState state, int new_val);

void set_zero(ProcState state, int new_val);

void set_parity(ProcState state, int new_val);

void set_carry(ProcState state, int new_val);

void set_aux_carry(ProcState state, int new_val);

void set_mem_byte(ProcState state, unsigned short mem_location, unsigned char new_val);

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(ProcState state, unsigned short mem_location,
  unsigned short data_length, unsigned char *data);

unsigned short get_reg_pair_b_c(ProcState state);

unsigned short get_reg_pair_d_e(ProcState state);

unsigned short get_reg_pair_h_l(ProcState state);

unsigned char get_reg_b(ProcState state);

unsigned char get_reg_c(ProcState state);

unsigned char get_reg_d(ProcState state);

unsigned char get_reg_e(ProcState state);

unsigned char get_reg_h(ProcState state);

unsigned char get_reg_l(ProcState state);

unsigned char get_reg_a(ProcState state);

unsigned short get_sp(ProcState state);

unsigned short get_pc(ProcState state);

int get_sign(ProcState state);

int get_zero(ProcState state);

int get_parity(ProcState state);

int get_carry(ProcState state);

int get_aux_carry(ProcState state);

unsigned char get_mem_byte(ProcState state, unsigned short mem_location);

int parity(unsigned char byte);

int sign(unsigned char byte);

int zero(unsigned char byte);

int add_carry(unsigned char byte_1, unsigned char byte_2);

int add_aux_carry(unsigned char byte_1, unsigned char byte_2);

unsigned char complement(unsigned char byte);

void print_registers(ProcState state);

void print_mem_r(unsigned short mem_addr, unsigned short pre_bytes, unsigned short post_bytes, ProcState *state);

void print_mem_c(unsigned short mem_addr, unsigned short post_bytes, ProcState *state);

void print_mem(unsigned short mem_addr, ProcState *state);
