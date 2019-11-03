#include <stdio.h>
#include "state.h"
#include "state_util.h"

const int BYTE_SIZE = 8;
const int DOUBLE_BYTE_SIZE = 16;
const int NIBBLE_SIZE = 4;

int nop(State8080 *state) {
  state->pc += 1;
  return 4;
}

int unused(State8080 *state) {
  printf("Encountered illegal instruction: addr 0x%x", state->pc);
  return 1;
}

int cmc(State8080 *state) {
  state->carry = !state->carry;
  state->pc += 1;
  return 4;
}

int stc(State8080 *state) {
  state->carry = 1;
  state->pc += 1;
  return 4;
}

int inr(unsigned char *data, State8080 *state) {
  (*data)++;
  state->zero = zero(*data);
  state->parity = parity(*data);
  state->sign = sign(*data);
  // TODO: Aux carry
  state->pc += 1;
  return 5;
}

int dcr(unsigned char *data, State8080 *state) {
  (*data)--;
  state->zero = zero(*data);
  state->parity = parity(*data);
  state->sign = sign(*data);
  // TODO: Aux carry
  state->pc += 1;
  return 5;
}

int cma(State8080 *state) {
  state->reg_a = ~state->reg_a;
  state->pc += 1;
  return 4;
}

int daa(State8080 *state) {

  // Note: this implementation does not pass the tests in the 
  // diagnostic script. Not sure why, seems like maybe the
  // specification for this instruction in the handbook might 
  // not be accurate.
  // As a result, I've stopped setting the Aux Carry bit in some
  // of the instructions because this is the only instruction
  // that relies on the Aux Carry being set.

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
  return 4;
}

int mov(unsigned char data_src, unsigned char *mem_addr_dst, State8080 *state) {
  *mem_addr_dst = data_src;
  state->pc += 1;
  return 7;
}

int stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, State8080 *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->mem[mem_addr] = state->reg_a;
  state->pc += 1;
  return 7;
}

int ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, State8080 *state) {
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->reg_a = state->mem[mem_addr];
  state->pc += 1;
  return 7;
}

int add(unsigned char data, State8080 *state) {
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
  return 4;
}

int adc(unsigned char data, State8080 *state) {
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
  return 4;
}

int sub(unsigned char data, State8080 *state) {
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
  return 4;
}

int sbb(unsigned char data, State8080 *state) {
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
  return 4;
}

int ana(unsigned char data, State8080 *state) {
  unsigned char result = state->reg_a & data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
  state->pc += 1;
  return 4;
}

int xra(unsigned char data, State8080 *state) {
  unsigned char result = state->reg_a ^ data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
  state->pc += 1;
  return 4;
}

int ora(unsigned char data, State8080 *state) {
  unsigned char result = state->reg_a | data;
  state->reg_a = result;
  state->carry = 0;
  state->aux_carry = 0;
  state->parity = parity(result);
  state->zero = zero(result);
  state->sign = sign(result);
  state->pc += 1;
  return 4;
}

int cmp(unsigned char data, State8080 *state) {
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
  return 4;
}

int rlc(State8080 *state) {
  unsigned int result = state->reg_a << 1;
  int carry_bit = (0x100 & result) >> BYTE_SIZE;
  result |= carry_bit;
  state->reg_a = result;
  state->carry = carry_bit;
  state->pc += 1;
  return 4;
}

int rrc(State8080 *state) {
  int carry_bit = (0x1 & state->reg_a);
  unsigned int result = state->reg_a >> 1;
  result |= carry_bit << (BYTE_SIZE - 1);
  state->reg_a = result;
  state->carry = carry_bit;
  state->pc += 1;
  return 4;
}

int ral(State8080 *state) {
  unsigned int result = state->reg_a << 1;
  int old_carry_bit = state->carry;
  int new_carry_bit = (0x100 & result) >> BYTE_SIZE;
  result |= old_carry_bit;
  state->reg_a = result;
  state->carry = new_carry_bit;
  state->pc += 1;
  return 4;
}

int rar(State8080 *state) {
  int new_carry_bit = (0x1 & state->reg_a);
  unsigned int result = state->reg_a >> 1;
  int old_carry_bit = state->carry;
  result |= old_carry_bit << (BYTE_SIZE - 1);
  state->reg_a = result;
  state->carry = new_carry_bit;
  state->pc += 1;
  return 4;
}

int push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, State8080 *state) {
  unsigned short sp = state->sp;
  state->mem[sp-1] = mem_addr_hi;
  state->mem[sp-2] = mem_addr_lo;
  state->sp -= 2;
  state->pc += 1;
  return 11;
}

int push_psw(State8080 *state) {
  unsigned char psw_bits = 0 |
   state->sign << 7 |
   state->zero << 6 |
   state->aux_carry << 4 |
   state->parity << 2 |
   1 << 1 |
   state->carry;
   push(state->reg_a, psw_bits, state);
   return 11;
}

int pop(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, State8080 *state) {
  unsigned short sp = state->sp;
  *mem_addr_lo = state->mem[sp];
  *mem_addr_hi = state->mem[sp+1];
  state->sp += 2;
  state->pc += 1;
  return 10;
}

int pop_psw(State8080 *state) {
  unsigned char psw_bits;
  pop(&state->reg_a, &psw_bits, state);
  state->sign = (0x80 & psw_bits) >> 7;
  state->zero = (0x40 & psw_bits) >> 6;
  state->aux_carry = (0x10 & psw_bits >> 4);
  state->parity = (0x04 & psw_bits) >> 2;
  state->carry = (0x01 & psw_bits);
  return 10;
}

int dad_16(unsigned short *data, State8080 *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  unsigned int sum = hl_bits + (*data);
  int carry_bit = (0x10000 & sum) >> DOUBLE_BYTE_SIZE;
  state->reg_h = sum >> BYTE_SIZE;
  state->reg_l = sum;
  state->carry = carry_bit;
  state->pc += 1;
  return 10;
}

int dad(unsigned char data_hi, unsigned char data_lo, State8080 *state) {
  unsigned short in_bits = (data_hi << BYTE_SIZE) ^ data_lo;
  dad_16(&in_bits, state);
  return 10;
}

int inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, State8080 *state) {
  unsigned short in_bits = (*mem_addr_hi << BYTE_SIZE) ^ *mem_addr_lo;
  in_bits++;
  *mem_addr_hi = in_bits >> BYTE_SIZE;
  *mem_addr_lo = in_bits;
  state->pc += 1;
  return 5;
}

int inx_16(unsigned short *data, State8080 *state) {
  (*data)++;
  state->pc += 1;
  return 5;
}

int dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, State8080 *state) {
  unsigned short in_bits = (*mem_addr_hi << BYTE_SIZE) ^ *mem_addr_lo;
  in_bits--;
  *mem_addr_hi = in_bits >> BYTE_SIZE;
  *mem_addr_lo = in_bits;
  state->pc += 1;
  return 5;
}

int dcx_16(unsigned short *data, State8080 *state) {
  (*data)--;
  state->pc += 1;
  return 5;
}

int xchg(State8080 *state) {
  unsigned char temp_a = state->reg_h;
  unsigned char temp_b = state->reg_l;
  state->reg_h = state->reg_d;
  state->reg_l = state->reg_e;
  state->reg_d = temp_a;
  state->reg_e = temp_b;
  state->pc += 1;
  return 4;
}

int xthl(State8080 *state) {
  unsigned char temp_a = state->reg_h;
  unsigned char temp_b = state->reg_l;
  state->reg_h = state->mem[state->sp + 1];
  state->reg_l = state->mem[state->sp];
  state->mem[state->sp + 1] = temp_a;
  state->mem[state->sp] = temp_b;
  state->pc += 1;
  return 18;
}

int sphl(State8080 *state) {
  unsigned short hl_bits = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  state->sp = hl_bits;
  state->pc += 1;
  return 5;
}

int lxi(unsigned char *dest_hi, unsigned char *dest_lo, State8080 *state) {
  *dest_hi = state->mem[state->pc+2];
  *dest_lo = state->mem[state->pc+1];
  state->pc += 3;
  return 10;
}

int lxi_16(unsigned short *dest, State8080 *state) {
  *dest = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->pc += 3;
  return 10;
}

int mvi(unsigned char *dest, State8080 *state) {
  *dest = state->mem[state->pc+1];
  state->pc += 2;
  return 7;
}

int mvi_m(unsigned char *dest, State8080 *state) {
	mvi(dest, state);
	return 10;
}

int adi(State8080 *state) {
  add(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int aci(State8080 *state) {
  adc(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int sui(State8080 *state) {
  sub(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int sbi(State8080 *state) {
  sbb(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int ani(State8080 *state) {
  ana(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int xri(State8080 *state) {
  xra(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int ori(State8080 *state) {
  ora(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int cpi(State8080 *state) {
  cmp(state->mem[state->pc+1], state);
  state->pc += 1;
  return 7;
}

int sta(State8080 *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->mem[mem_addr] = state->reg_a;
  state->pc += 3;
  return 13;
}

int lda(State8080 *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->reg_a = state->mem[mem_addr];
  state->pc += 3;
  return 13;
}

int shld(State8080 *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->mem[mem_addr] = state->reg_l;
  state->mem[mem_addr + 1] = state->reg_h;
  state->pc += 3;
  return 16;
}

int lhld(State8080 *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->reg_l = state->mem[mem_addr];
  state->reg_h = state->mem[mem_addr + 1];
  state->pc += 3;
  return 16;
}

int pchl(State8080 *state) {
  unsigned short mem_addr = (state->reg_h << BYTE_SIZE) ^ state->reg_l;
  state->pc = mem_addr;
  return 5;
}

int jmp(State8080 *state) {
  unsigned short mem_addr = (state->mem[state->pc+2] << BYTE_SIZE) ^ state->mem[state->pc+1];
  state->pc = mem_addr;
  return 10;
}

int jc(State8080 *state) {
  if (state->carry) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jnc(State8080 *state) {
  if (!state->carry) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jz(State8080 *state) {
  if (state->zero) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jnz(State8080 *state) {
  if (!state->zero) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jm(State8080 *state) {
  if (state->sign) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jp(State8080 *state) {
  if (!state->sign) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jpe(State8080 *state) {
  if (state->parity) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

int jpo(State8080 *state) {
  if (!state->parity) {
    jmp(state);
  } else {
    state->pc += 3;
  }
  return 10;
}

void _call(unsigned char mem_addr_hi, unsigned char mem_addr_lo, unsigned short instr_size, State8080 *state) {
  unsigned short return_addr = state->pc + instr_size;
  push(return_addr >> BYTE_SIZE, return_addr, state);
  unsigned short mem_addr = (mem_addr_hi << BYTE_SIZE) ^ mem_addr_lo;
  state->pc = mem_addr;
}

int call(State8080 *state) {
  _call(state->mem[state->pc+2], state->mem[state->pc+1], 3, state);
  return 17;
}

int cc(State8080 *state) {
  if (state->carry) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cnc(State8080 *state) {
  if (!state->carry) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cz(State8080 *state) {
  if (state->zero) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cnz(State8080 *state) {
  if (!state->zero) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cm(State8080 *state) {
  if (state->sign) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cp(State8080 *state) {
  if (!state->sign) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cpe(State8080 *state) {
  if (state->parity) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int cpo(State8080 *state) {
  if (!state->parity) {
    call(state);
    return 17;
  } else {
    state->pc += 3;
    return 11;
  }
}

int ret(State8080 *state) {
  unsigned char return_addr_hi;
  unsigned char return_addr_lo;
  pop(&return_addr_hi, &return_addr_lo, state);
  unsigned short return_addr = (return_addr_hi << BYTE_SIZE) ^ return_addr_lo;
  state->pc = return_addr;
  return 10;
}

int rc(State8080 *state) {
  if (state->carry) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rnc(State8080 *state) {
  if (!state->carry) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rz(State8080 *state) {
  if (state->zero) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rnz(State8080 *state) {
  if (!state->zero) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rm(State8080 *state) {
  if (state->sign) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rp(State8080 *state) {
  if (!state->sign) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rpe(State8080 *state) {
  if (state->parity) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rpo(State8080 *state) {
  if (!state->parity) {
    ret(state);
    return 11;
  } else {
    state->pc += 1;
    return 5;
  }
}

int rst(unsigned char exp, State8080 *state) {
  unsigned short jump_addr = (exp << 3) & 0x0038; // L.S. 3 bits of exp shifted 3 bits right
  _call(jump_addr >> BYTE_SIZE, jump_addr, 1, state); // Do a "CALL" type function
  return 11;
}

int ei(State8080 *state) {
  state->inte = 1;
  state->pc += 1;
  return 4;
}

int di(State8080 *state) {
  state->inte = 0;
  state->pc += 1;
  return 4;
}

int in(State8080 *state) {
  unsigned char port = state->mem[state->pc+1];
  state->reg_a = (state->inputs[port])();
  state->pc += 2;
  return 10;
}

int out(State8080 *state) {
  unsigned char port = state->mem[state->pc+1];
  (state->outputs[port])(state->reg_a);
  state->pc += 2;
  return 10;
}

int hlt(State8080 *state) {
	printf("Encountered HLT instruction: addr 0x%x", state->pc);
	return 1;
}
