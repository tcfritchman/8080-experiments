#include "state.h"
#include "state_util.h"

const int BYTE_SIZE = 8;

void addx(unsigned char *mem_addr, ProcState *state) {
  unsigned int sum = *mem_addr + state->reg_a;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (*mem_addr & 0xf) + (state->reg_a & 0xf);
  int aux_carry_bit = (0x10 & aux_sum) >> (BYTE_SIZE / 2);
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = carry_bit;
  state->aux_carry = aux_carry_bit;
}

void adcx(unsigned char *mem_addr, ProcState *state) {
  unsigned int sum = *mem_addr + state->reg_a + state->carry;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (*mem_addr & 0xf) + (state->reg_a & 0xf) + state->carry;
  int aux_carry_bit = (0x10 & aux_sum) >> (BYTE_SIZE / 2);
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = carry_bit;
  state->aux_carry = aux_carry_bit;
}