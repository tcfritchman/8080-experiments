#include <stdio.h>
#include "state.h"
#include "state_util.h"

const int BYTE_SIZE = 8;
const int DOUBLE_BYTE_SIZE = 16;
const int NIBBLE_SIZE = 4;

void nop(ProcState *state) {
  state->pc += 1;
}

void unused(ProcState *state) {
  printf("Encountered illegal instruction: addr 0x%x", state->pc);
}

void cmc(ProcState *state) {
  state->carry = !state->carry;
  state->pc += 1;
}

void stc(ProcState *state) {
  state->carry = 1;
  state->pc += 1; 
}

void inr(unsigned char *data, ProcState *state) {
  (*data)++;
  state->pc += 1;
}

void dcr(unsigned char *data, ProcState *state) {
  (*data)--;
  state->pc += 1;
}

void cma(ProcState *state) {
  state->reg_a = ~state->reg_a;
  state->pc += 1;
}

void daa(ProcState *state) {

  // Note: this implementation does not pass the tests in the 
  // diagnostic script. Not sure why, seems like maybe the
  // specification for this instruction in the handbook might 
  // not be accurate.

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
  state->pc += 1;
}

void mov(unsigned char data_src, unsigned char *mem_addr_dst, ProcState *state) {
  *mem_addr_dst = data_src;
  state->pc += 1;
}

void stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->mem[mem_addr] = state->reg_a;
  state->pc += 1;
}

void ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->reg_a = state->mem[mem_addr];
  state->pc += 1;
}

void add(unsigned char data, ProcState *state) {
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
  state->pc += 1;
}

void adc(unsigned char data, ProcState *state) {
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
  state->pc += 1;
}

void sub(unsigned char data, ProcState *state) {
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
  state->pc += 1;
}

void sbb(unsigned char data, ProcState *state) {
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
  state->pc += 1;
}

void ana(unsigned char data, ProcState *state) {
  unsigned char result = state->reg_a & data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
  state->pc += 1;
}

void xra(unsigned char data, ProcState *state) {
  unsigned char result = state->reg_a ^ data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
  state->pc += 1;
}

void ora(unsigned char data, ProcState *state) {
  unsigned char result = state->reg_a | data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
  state->pc += 1;
}

void cmp(unsigned char data, ProcState *state) {
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
  state->pc += 1;
}

void rlc(ProcState *state) {
  unsigned int result = state->reg_a << 1;
  int carry_bit = (0x100 & result) >> BYTE_SIZE;
  result |= carry_bit;
  state->reg_a = result;
  state->carry = carry_bit;
  state->pc += 1;
}

void rrc(ProcState *state) {
  int carry_bit = (0x1 & state->reg_a);
  unsigned int result = state->reg_a >> 1;
  result |= carry_bit << (BYTE_SIZE - 1);
  state->reg_a = result;
  state->carry = carry_bit;
  state->pc += 1;
}

void ral(ProcState *state) {
  unsigned int result = state->reg_a << 1;
  int old_carry_bit = state->carry;
  int new_carry_bit = (0x100 & result) >> BYTE_SIZE;
  result |= old_carry_bit;
  state->reg_a = result;
  state->carry = new_carry_bit;
  state->pc += 1;
}

void rar(ProcState *state) {
  int new_carry_bit = (0x1 & state->reg_a);
  unsigned int result = state->reg_a >> 1;
  int old_carry_bit = state->carry;
  result |= old_carry_bit << (BYTE_SIZE - 1);
  state->reg_a = result;
  state->carry = new_carry_bit;
  state->pc += 1;
}

void push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state) {
  unsigned short sp = state->sp;
  state->mem[sp-1] = mem_addr_hi;
  state->mem[sp-2] = mem_addr_lo;
  state->sp -= 2;
  state->pc += 1;
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
  state->pc += 1;
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

void dad_16(unsigned short *data, ProcState *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  unsigned int sum = hl_bits + (*data);
  int carry_bit = (0x10000 & sum) >> DOUBLE_BYTE_SIZE;
  state->reg_h = sum >> BYTE_SIZE;
  state->reg_l = sum;
  state->carry = carry_bit;
  state->pc += 1;
}

void dad(unsigned char data_hi, unsigned char data_lo, ProcState *state) {
  unsigned short in_bits = (data_hi << BYTE_SIZE) ^ data_lo;
  dad_16(&in_bits, state);
}

void inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state) {
  unsigned short in_bits = (*mem_addr_hi << BYTE_SIZE) ^ *mem_addr_lo;
  in_bits++;
  *mem_addr_hi = in_bits >> BYTE_SIZE;
  *mem_addr_lo = in_bits;
  state->pc += 1;
}

void inx_16(unsigned short *data, ProcState *state) {
  (*data)++;
  state->pc += 1;
}

void dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state) {
  unsigned short in_bits = (*mem_addr_hi << BYTE_SIZE) ^ *mem_addr_lo;
  in_bits--;
  *mem_addr_hi = in_bits >> BYTE_SIZE;
  *mem_addr_lo = in_bits;
  state->pc += 1;
}

void dcx_16(unsigned short *data, ProcState *state) {
  (*data)--;
  state->pc += 1;
}

void xchg(ProcState *state) {
  unsigned char temp_a = state->reg_h;
  unsigned char temp_b = state->reg_l;
  state->reg_h = state->reg_d;
  state->reg_l = state->reg_e;
  state->reg_d = temp_a;
  state->reg_e = temp_b;
  state->pc += 1;
}

void xthl(ProcState *state) {
  unsigned char temp_a = state->reg_h;
  unsigned char temp_b = state->reg_l;
  state->reg_h = state->mem[state->sp + 1];
  state->reg_l = state->mem[state->sp];
  state->mem[state->sp + 1] = temp_a;
  state->mem[state->sp] = temp_b;
  state->pc += 1;
}

void sphl(ProcState *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  state->sp = hl_bits;
  state->pc += 1;
}

void lxi(unsigned char *dest_hi, unsigned char *dest_lo, ProcState *state) {
  *dest_hi = state->mem[state->pc+2];
  *dest_lo = state->mem[state->pc+1];
  state->pc += 3;
}

void lxi_16(unsigned short *dest, ProcState *state) {
  *dest = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->pc += 3;
}

void mvi(unsigned char *dest, ProcState *state) {
  *dest = state->mem[state->pc+1];
  state->pc += 2;
}

void adi(ProcState *state) {
  add(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void aci(ProcState *state) {
  adc(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void sui(ProcState *state) {
  sub(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void sbi(ProcState *state) {
  sbb(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void ani(ProcState *state) {
  ana(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void xri(ProcState *state) {
  xra(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void ori(ProcState *state) {
  ora(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void cpi(ProcState *state) {
  cmp(state->mem[state->pc+1], state);
  state->pc += 1; // Progress PC 1 additional byte
}

void sta(ProcState *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->mem[mem_addr] = state->reg_a;
  state->pc += 3;
}

void lda(ProcState *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->reg_a = state->mem[mem_addr];
  state->pc += 3;
}

void shld(ProcState *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->mem[mem_addr] = state->reg_l;
  state->mem[mem_addr + 1] = state->reg_h;
  state->pc += 3;
}

void lhld(ProcState *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->reg_l = state->mem[mem_addr];
  state->reg_h = state->mem[mem_addr + 1];
  state->pc += 3;
}

void pchl(ProcState *state) {
  unsigned short mem_addr = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  state->pc = mem_addr;
}

void jmp(ProcState *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->pc = mem_addr;
}

void jc(ProcState *state) {
  if (state->carry) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jnc(ProcState *state) {
  if (!state->carry) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jz(ProcState *state) {
  if (state->zero) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jnz(ProcState *state) {
  if (!state->zero) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jm(ProcState *state) {
  if (state->sign) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jp(ProcState *state) {
  if (!state->sign) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jpe(ProcState *state) {
  if (state->parity) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void jpo(ProcState *state) {
  if (!state->parity) {
    jmp(state);
  } else {
    state->pc += 3;
  }
}

void _call(unsigned char mem_addr_hi, unsigned char mem_addr_lo, unsigned short instr_size, ProcState *state) {
  unsigned short return_addr = state->pc + instr_size;
  push(return_addr >> BYTE_SIZE, return_addr, state);
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->pc = mem_addr;
}

void call(ProcState *state) {
  _call(state->mem[state->pc+2], state->mem[state->pc+1], 3, state);
}

void cc(ProcState *state) {
  if (state->carry) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cnc(ProcState *state) {
  if (!state->carry) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cz(ProcState *state) {
  if (state->zero) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cnz(ProcState *state) {
  if (!state->zero) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cm(ProcState *state) {
  if (state->sign) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cp(ProcState *state) {
  if (!state->sign) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cpe(ProcState *state) {
  if (state->parity) {
    call(state);
  } else {
    state->pc += 3;
  }
}

void cpo(ProcState *state) {
  if (!state->parity) {
    call(state);
  } else {
    state->pc += 3;
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
  } else {
    state->pc += 1;
  }
}

void rnc(ProcState *state) {
  if (!state->carry) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rz(ProcState *state) {
  if (state->zero) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rnz(ProcState *state) {
  if (!state->zero) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rm(ProcState *state) {
  if (state->sign) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rp(ProcState *state) {
  if (!state->sign) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rpe(ProcState *state) {
  if (state->parity) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rpo(ProcState *state) {
  if (!state->parity) {
    ret(state);
  } else {
    state->pc += 1;
  }
}

void rst(unsigned char exp, ProcState *state) {
  unsigned short jump_addr = (exp << 3) & 0x0038; // L.S. 3 bits of exp shifted 3 bits right
  _call(jump_addr >> BYTE_SIZE, jump_addr, 1, state); // Do a "CALL" type function
}

void ei(ProcState *state) {
  state->inte = 1;
  state->pc += 1;
}

void di(ProcState *state) {
  state->inte = 0;
  state->pc += 1;
}

void in(ProcState *state) {
  // TODO
  state->pc += 2;
}

void out(ProcState *state) {
  // TODO
  state->pc += 2;
}

void hlt(ProcState *state) {
  // TODO
}