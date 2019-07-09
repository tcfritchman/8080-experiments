#include "state.h"
#include "state_util.h"

const int BYTE_SIZE = 8;
const int DOUBLE_BYTE_SIZE = 16;
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

void rrc(ProcState *state) {
  int carry_bit = (0x1 & state->reg_a);
  unsigned int result = state->reg_a >> 1;
  result |= carry_bit << (BYTE_SIZE - 1);
  state->reg_a = result;
  state->carry = carry_bit;
}

void ral(ProcState *state) {
  unsigned int result = state->reg_a << 1;
  int old_carry_bit = state->carry;
  int new_carry_bit = (0x100 & result) >> BYTE_SIZE;
  result |= old_carry_bit;
  state->reg_a = result;
  state->carry = new_carry_bit;
}

void rar(ProcState *state) {
  int new_carry_bit = (0x1 & state->reg_a);
  unsigned int result = state->reg_a >> 1;
  int old_carry_bit = state->carry;
  result |= old_carry_bit << (BYTE_SIZE - 1);
  state->reg_a = result;
  state->carry = new_carry_bit;
}

void push(unsigned char *mem_addr_1, unsigned char *mem_addr_2, ProcState *state) {
  unsigned short sp = state->sp;
  state->mem[sp-1] = *mem_addr_1;
  state->mem[sp-2] = *mem_addr_2;
  state->sp -= 2;
}

void push_psw(ProcState *state) {
  unsigned char psw_bits = 0 |
   state->sign << 7 |
   state->zero << 6 |
   state->aux_carry << 4 |
   state->parity << 2 |
   1 << 1 |
   state->carry;
   push(&state->reg_a, &psw_bits, state);
}

void pop(unsigned char *mem_addr_1, unsigned char *mem_addr_2, ProcState *state) {
  unsigned short sp = state->sp;
  *mem_addr_2 = state->mem[sp];
  *mem_addr_1 = state->mem[sp+1];
  state->sp += 2;
}

void pop_psw(ProcState *state) {
  unsigned char psw_bits;
  pop(&state->reg_a, &psw_bits, state);
  state->sign = (0x80 & psw_bits) >> 7;
  state->zero = (0x40 & psw_bits) >> 6;
  state->aux_carry = (0x10 & psw_bits >> 4);
  state->parity = (0x04 & psw_bits) >> 2;
  state->carry = (0x01 & psw_bits);
}

void dad(unsigned char *mem_addr_1, unsigned char *mem_addr_2, ProcState *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  unsigned short in_bits = (*mem_addr_1 << BYTE_SIZE) ^ *mem_addr_2;
  unsigned int sum = hl_bits + in_bits;
  int carry_bit = (0x10000 & sum) >> DOUBLE_BYTE_SIZE;
  state->reg_h = sum >> BYTE_SIZE;
  state->reg_l = sum;
  state->carry = carry_bit;
}

void inx(unsigned char *mem_addr_1, unsigned char *mem_addr_2) {
  unsigned short in_bits = (*mem_addr_1 << BYTE_SIZE) ^ *mem_addr_2;
  in_bits++;
  *mem_addr_1 = in_bits >> BYTE_SIZE;
  *mem_addr_2 = in_bits;
}

void dcx(unsigned char *mem_addr_1, unsigned char *mem_addr_2) {
  unsigned short in_bits = (*mem_addr_1 << BYTE_SIZE) ^ *mem_addr_2;
  in_bits--;
  *mem_addr_1 = in_bits >> BYTE_SIZE;
  *mem_addr_2 = in_bits;
}