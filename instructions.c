#include "state.h"
#include "state_util.h"

const int BYTE_SIZE = 8;
const int NIBBLE_SIZE = 4;

void addx(unsigned char *mem_addr, ProcState *state) {
  unsigned int sum = *mem_addr + state->reg_a;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (*mem_addr & 0xf) + (state->reg_a & 0xf);
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
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
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = carry_bit;
  state->aux_carry = aux_carry_bit;
}

void subx(unsigned char *mem_addr, ProcState *state) {
  // Flip only the last 8 bits of the value in mem_addr
  unsigned int mem_addr_flipped = (~(*mem_addr | (~0xff)));
  // Perform sums using 2's compliment subtraction
  unsigned int sum = state->reg_a + mem_addr_flipped + 1;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (state->reg_a & 0xf) + ((~*mem_addr) & 0xf) + 1;
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = !carry_bit;
  state->aux_carry = aux_carry_bit;
}

void sbbx(unsigned char *mem_addr, ProcState *state) {
  // Flip only the last 8 bits of the value in mem_addr
  unsigned int mem_addr_flipped = (~((*mem_addr + state->carry) | (~0xff)));
  // Perform sums using 2's compliment subtraction
  unsigned int sum = state->reg_a + mem_addr_flipped + 1;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (state->reg_a & 0xf) + ((~(*mem_addr + state->carry)) & 0xf) + 1;
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = !carry_bit;
  state->aux_carry = aux_carry_bit;
}

void anax(unsigned char *mem_addr, ProcState *state) {
  unsigned char result = state->reg_a & *mem_addr;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
}

void xrax(unsigned char *mem_addr, ProcState *state) {
  unsigned char result = state->reg_a ^ *mem_addr;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
}

void orax(unsigned char *mem_addr, ProcState *state) {
  unsigned char result = state->reg_a | *mem_addr;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
}

void cmpx(unsigned char *mem_addr, ProcState *state) {
  // Flip only the last 8 bits of the value in mem_addr
  unsigned int mem_addr_flipped = (~(*mem_addr | (~0xff)));
  // Perform sums using 2's compliment subtraction
  unsigned int sum = state->reg_a + mem_addr_flipped + 1;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (state->reg_a & 0xf) + ((~*mem_addr) & 0xf) + 1;
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = !carry_bit;
  state->aux_carry = aux_carry_bit;
}

void rlc(ProcState *state) {
  unsigned int result = state->reg_a << 1;
  int carry_bit = (0x100 & result) >> BYTE_SIZE;
  result |= carry_bit;
  state->reg_a = result;
  state->carry = carry_bit;
}