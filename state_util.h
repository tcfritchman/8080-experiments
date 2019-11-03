#include "state.h"

int parity(unsigned char byte);

int sign(unsigned char byte);

int zero(unsigned char byte);

void print_registers_compact(State8080 *state);

void print_registers(State8080 state);

void print_mem_r(unsigned short mem_addr, unsigned short pre_bytes, unsigned short post_bytes, State8080 *state);

void print_mem_c(unsigned short mem_addr, unsigned short post_bytes, State8080 *state);

void print_mem(unsigned short mem_addr, State8080 *state);

unsigned char *get_mem_byte(State8080 *state);