#include "state.h"

void set_reg_b(ProcState state, char new_val);

void set_reg_c(ProcState state, char new_val);

void set_reg_d(ProcState state, char new_val);

void set_reg_e(ProcState state, char new_val);

void set_reg_h(ProcState state, char new_val);

void set_reg_l(ProcState state, char new_val);

void set_reg_a(ProcState state, char new_val);

void set_sp(ProcState state, unsigned short new_val);

void set_pc(ProcState state, unsigned short new_val);

void set_sign(ProcState state, int new_val);

void set_zero(ProcState state, int new_val);

void set_parity(ProcState state, int new_val);

void set_carry(ProcState state, int new_val);

void set_aux_carry(ProcState state, int new_val);

void set_mem_byte(ProcState state, unsigned short mem_location, char new_val);

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(ProcState state, unsigned short mem_location,
  unsigned short data_length, char *data);

short get_reg_pair_b_c(ProcState state);

short get_reg_pair_d_e(ProcState state);

short get_reg_pair_h_l(ProcState state);

char get_reg_b(ProcState state);

char get_reg_c(ProcState state);

char get_reg_d(ProcState state);

char get_reg_e(ProcState state);

char get_reg_h(ProcState state);

char get_reg_l(ProcState state);

char get_reg_a(ProcState state);

unsigned short get_sp(ProcState state);

unsigned short get_pc(ProcState state);

int get_sign(ProcState state);

int get_zero(ProcState state);

int get_parity(ProcState state);

int get_carry(ProcState state);

int get_aux_carry(ProcState state);

char get_mem_byte(ProcState state, unsigned short mem_location);

int parity(char byte);

int sign(char byte);

int zero(char byte);

int add_carry(char byte_1, char byte_2);

int add_aux_carry(char byte_1, char byte_2);

char complement(char byte);
