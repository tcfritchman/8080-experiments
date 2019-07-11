#include "state.h"
#include "state_util.h"

const int BYTE_SIZE = 8;
const int DOUBLE_BYTE_SIZE = 16;
const int NIBBLE_SIZE = 4;

void cmc(ProcState *state) {
  state->carry = !state->carry;
}

void stc(ProcState *state) {
  state->carry = 1;
}

void inr(unsigned char *data) {
  *data++;
}

void dcr(unsigned char *data) {
  *data--;
}

void cma(ProcState *state) {
  state->reg_a = ~state->reg_a;
}

void daa(ProcState *state) {
  unsigned char lo_four = (state->reg_a & 0x0f);
  if (lo_four > 9 || state->aux_carry) {
    lo_four += 6;
    state->aux_carry = (lo_four > 0xf);
    state->reg_a += 6;
  }
  unsigned char hi_four = (state->reg_a >> NIBBLE_SIZE);
  if (hi_four > 9 || state->carry) {
    hi_four += 6;
    if (hi_four > 0xf) {
      state->carry = 1;
    }
    state->reg_a += ((hi_four + 6) << NIBBLE_SIZE);
  }
  state->parity = parity(state->reg_a);
  state->zero = zero(state->reg_a);
  state->sign = sign(state->reg_a);
}

void mov(unsigned char data_src, unsigned char *mem_addr_dst) {
  *mem_addr_dst = data_src;
}

void stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->mem[mem_addr] = state->reg_a;
}

void ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->reg_a = state->mem[mem_addr];
}

void addx(unsigned char data, ProcState *state) {
  unsigned int sum = data + state->reg_a;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (data & 0xf) + (state->reg_a & 0xf);
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = carry_bit;
  state->aux_carry = aux_carry_bit;
}

void adcx(unsigned char data, ProcState *state) {
  unsigned int sum = data + state->reg_a + state->carry;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (data & 0xf) + (state->reg_a & 0xf) + state->carry;
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = carry_bit;
  state->aux_carry = aux_carry_bit;
}

void subx(unsigned char data, ProcState *state) {
  // Flip only the last 8 bits of the value in data
  unsigned int data_flipped = (~(data | (~0xff)));
  // Perform sums using 2's compliment subtraction
  unsigned int sum = state->reg_a + data_flipped + 1;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (state->reg_a & 0xf) + ((~data) & 0xf) + 1;
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = !carry_bit;
  state->aux_carry = aux_carry_bit;
}

void sbbx(unsigned char data, ProcState *state) {
  // Flip only the last 8 bits of the value in data
  unsigned int data_flipped = (~((data + state->carry) | (~0xff)));
  // Perform sums using 2's compliment subtraction
  unsigned int sum = state->reg_a + data_flipped + 1;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (state->reg_a & 0xf) + ((~(data + state->carry)) & 0xf) + 1;
  int aux_carry_bit = (0x10 & aux_sum) >> NIBBLE_SIZE;
  state->reg_a = sum;
  state->parity = parity(sum);
  state->zero = zero(sum);
  state->sign = sign(sum);
  state->carry = !carry_bit;
  state->aux_carry = aux_carry_bit;
}

void anax(unsigned char data, ProcState *state) {
  unsigned char result = state->reg_a & data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
}

void xrax(unsigned char data, ProcState *state) {
  unsigned char result = state->reg_a ^ data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
}

void orax(unsigned char data, ProcState *state) {
  unsigned char result = state->reg_a | data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
}

void cmpx(unsigned char data, ProcState *state) {
  // Flip only the last 8 bits of the value in data
  unsigned int data_flipped = (~(data | (~0xff)));
  // Perform sums using 2's compliment subtraction
  unsigned int sum = state->reg_a + data_flipped + 1;
  int carry_bit = (0x100 & sum) >> BYTE_SIZE;
  unsigned int aux_sum = (state->reg_a & 0xf) + ((~data) & 0xf) + 1;
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

void push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short sp = state->sp;
  state->mem[sp-1] = mem_addr_hi;
  state->mem[sp-2] = mem_addr_lo;
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
   push(state->reg_a, psw_bits, state);
}

void pop(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state) {
  unsigned short sp = state->sp;
  *mem_addr_lo = state->mem[sp];
  *mem_addr_hi = state->mem[sp+1];
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

void dad(unsigned char data_hi, unsigned char data_lo, ProcState *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  unsigned short in_bits = (data_hi << BYTE_SIZE) ^ data_lo;
  unsigned int sum = hl_bits + in_bits;
  int carry_bit = (0x10000 & sum) >> DOUBLE_BYTE_SIZE;
  state->reg_h = sum >> BYTE_SIZE;
  state->reg_l = sum;
  state->carry = carry_bit;
}

void inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo) {
  unsigned short in_bits = (*mem_addr_hi << BYTE_SIZE) ^ *mem_addr_lo;
  in_bits++;
  *mem_addr_hi = in_bits >> BYTE_SIZE;
  *mem_addr_lo = in_bits;
}

void dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo) {
  unsigned short in_bits = (*mem_addr_hi << BYTE_SIZE) ^ *mem_addr_lo;
  in_bits--;
  *mem_addr_hi = in_bits >> BYTE_SIZE;
  *mem_addr_lo = in_bits;
}

void xchg(ProcState *state) {
  unsigned char temp_a = state->reg_h;
  unsigned char temp_b = state->reg_l;
  state->reg_h = state->reg_d;
  state->reg_l = state->reg_e;
  state->reg_d = temp_a;
  state->reg_e = temp_b;
}

void xthl(ProcState *state) {
  unsigned char temp_a = state->reg_h;
  unsigned char temp_b = state->reg_l;
  state->reg_h = state->mem[state->sp + 1];
  state->reg_l = state->mem[state->sp];
  state->mem[state->sp + 1] = temp_a;
  state->mem[state->sp] = temp_b;
}

void sphl(ProcState *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  state->sp = hl_bits;
}

void sta(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->mem[mem_addr] = state->reg_a;
}

void lda(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->reg_a = state->mem[mem_addr];
}

void shld(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->mem[mem_addr] = state->reg_l;
  state->mem[mem_addr + 1] = state->reg_h;
}

void lhld(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->reg_l = state->mem[mem_addr];
  state->reg_h = state->mem[mem_addr + 1];
}

void pchl(ProcState *state) {
  unsigned short mem_addr = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  state->pc = mem_addr;
}

void jmp(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->pc = mem_addr;
}

void jc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->carry) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jnc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->carry) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->zero) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jnz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->zero) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jm(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->sign) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jp(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->sign) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jpe(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->parity) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void jpo(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->parity) {
    jmp(mem_addr_hi, mem_addr_lo, state);
  }
}

void call(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short return_addr = state->pc + 3;
  push(return_addr >> BYTE_SIZE, return_addr, state);
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->pc = mem_addr;
}

void cc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->carry) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cnc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->carry) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->zero) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cnz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->zero) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cm(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->sign) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cp(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->sign) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cpe(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (state->parity) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void cpo(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  if (!state->parity) {
    call(mem_addr_hi, mem_addr_lo, state);
  }
}

void ret(ProcState *state) {
  unsigned char return_addr_hi;
  unsigned char return_addr_lo;
  pop(&return_addr_hi, &return_addr_lo, state);
  unsigned short return_addr = (return_addr_hi << BYTE_SIZE) ^ return_addr_lo;
  state->pc = return_addr;
}

void rc(ProcState *state) {
  if (state->carry) {
    ret(state);
  }
}

void rnc(ProcState *state) {
  if (!state->carry) {
    ret(state);
  }
}

void rz(ProcState *state) {
  if (state->zero) {
    ret(state);
  }
}

void rnz(ProcState *state) {
  if (!state->zero) {
    ret(state);
  }
}

void rm(ProcState *state) {
  if (state->sign) {
    ret(state);
  }
}

void rp(ProcState *state) {
  if (!state->sign) {
    ret(state);
  }
}

void rpe(ProcState *state) {
  if (state->parity) {
    ret(state);
  }
}

void rpo(ProcState *state) {
  if (!state->parity) {
    ret(state);
  }
}

void rst(unsigned char exp, ProcState *state) {
  unsigned short jump_addr = (exp << 3) & 0x0038; // L.S. 3 bits of exp shifted 3 bits right
  call(jump_addr >> BYTE_SIZE, jump_addr, state);
}

void ei(ProcState *state) {
  state->inte = 1;
}

void di(ProcState *state) {
  state->inte = 0;
}