#include <stdio.h>
#include "op_codes.h"
#include "state_util.h"
#include "instructions.h"
#include "state.h"

unsigned char TEST_BYTES[] = {0x78, 0xB1, 0xC8, 0x1A, 0x77, 0x13, 0x23, 0x0B, 0x78, 0xB1, 0xC2, 0x03, 0x10, 0xC9};

void update_state(ProcState *state) {
  unsigned short pc = state->pc;
  OpCode op_code = OP_CODES[state->mem[pc]];

  switch (op_code.code) {

    case 0x00:
      // NOP
      break;

    case 0x01:
      // LXI B
      lxi(state->mem[pc+2], state->mem[pc+1], &state->reg_b, &state->reg_c);
      break;

    case 0x02:
      // STAX B
      stax(state->reg_b, state->reg_c, state);
      break;

    case 0x03:
      // INX B
      inx(&state->reg_b, &state->reg_c);
      break;

    case 0x04:
      // INR B
      inr(&state->reg_b);
      break;

    case 0x05:
      // DCR B
      dcr(&state->reg_b);
      break;

    case 0x06:
      // MVI B
      mvi(state->mem[pc+1], &state->reg_b);
      break;

    case 0x07:
      // RLC
      rlc(state);
      break;

    case 0x08:
      // NONE
      break;

    case 0x09:
      // DAD B
      dad(state->reg_b, state->reg_c, state);
      break;

    case 0x0a:
      // LDAX B
      ldax(state->reg_b, state->reg_c, state);
      break;

    case 0x0b:
      // DCX B
      dcx(&state->reg_b, &state->reg_c);
      break;

    case 0x0c:
      // INR C
      inr(&state->reg_c);
      break;

    case 0x0d:
      // DCR C
      dcr(&state->reg_c);
      break;

    case 0x0e:
      // MVI C
      mvi(state->mem[pc+1], &state->reg_c);
      break;

    case 0x0f:
      // RRC
      rrc(state);
      break;

    case 0x10:
      // NONE
      break;

    case 0x11:
      // LXI D
      lxi(state->mem[pc+2], state->mem[pc+1], &state->reg_d, &state->reg_e);
      break;

    case 0x12:
      // STAX D
      stax(state->reg_d, state->reg_e, state);
      break;

    case 0x13:
      // INX D
      inx(&state->reg_d, &state->reg_e);
      break;

    case 0x14:
      // INR D
      inr(&state->reg_d);
      break;

    case 0x15:
      // DCR D
      dcr(&state->reg_d);
      break;

    case 0x16:
      // MVI D
      mvi(state->mem[pc+1], &state->reg_d);
      break;

    case 0x17:
      // RAL
      ral(state);
      break;

    case 0x18:
      // NONE
      break;

    case 0x19:
      // DAD D
      dad(state->reg_d, state->reg_e, state);
      break;

    case 0x1a:
      // LDAX D
      ldax(state->reg_d, state->reg_e, state);
      break;

    case 0x1b:
      // DCX D
      dcx(&state->reg_d, &state->reg_e);
      break;

    case 0x1c:
      // INR E
      inr(&state->reg_e);
      break;

    case 0x1d:
      // DCR E
      dcr(&state->reg_e);
      break;

    case 0x1e:
      // MVI E
      mvi(state->mem[pc+1], &state->reg_e);
      break;

    case 0x1f:
      // RAR
      rar(state);
      break;

    case 0x20:
      // NONE
      break;

    case 0x21:
      // LXI H
      lxi(state->mem[pc+2], state->mem[pc+1], &state->reg_h, &state->reg_l);
      break;

    case 0x22:
      // SHLD
      shld(state->mem[pc+2], state->mem[pc+1], state);
      break;

    case 0x23:
      // INX H
      inx(&state->reg_h, &state->reg_l);
      break;

    case 0x24:
      // INR H
      inr(&state->reg_h);
      break;

    case 0x25:
      // DCR H
      dcr(&state->reg_h);
      break;

    case 0x26:
      // MVI H
      mvi(state->mem[pc+1], &state->reg_h);
      break;

    case 0x27:
      // DAA
      daa(state);
      break;

    case 0x28:
      // NONE
      break;

    case 0x29:
      // DAD H
      dad(state->reg_h, state->reg_l, state);
      break;

    case 0x2a:
      // LHLD
      lhld(state->mem[pc+2], state->mem[pc+1], state);
      break;

    case 0x2b:
      // DCX H
      dcx(&state->reg_h, &state->reg_l);
      break;

    case 0x2c:
      // INR L
      inr(&state->reg_l);
      break;

    case 0x2d:
      // DCR L
      dcr(&state->reg_l);
      break;

    case 0x2e:
      // MVI L
      mvi(state->mem[pc+1], &state->reg_l);
      break;

    case 0x2f:
      // CMA
      cma(state);
      break;

    case 0x30:
      // NONE
      break;

    case 0x31:
      // LXI SP
      // TODO: Make helper functions for getting SP as bytes
      break;

    case 0x32:
      // STA
      sta(state->mem[pc+2], state->mem[pc+1], state);
      break;

    case 0x33:
      // INX SP
      // TODO
      break;

    case 0x34:
      // INR M
      // TODO: Special function?
      break;

    case 0x35:
      // DCR M
      // TODO
      break;

    case 0x36:
      // MVI M
      // TODO
      break;

    case 0x37:
      // STC
      stc(state);
      break;

    case 0x38:
      // NONE
      break;

    case 0x39:
      // DAD SP
      // TODO
      break;

    case 0x3a:
      // LDA
      lda(state->mem[pc+2], state->mem[pc+1], state);
      break;

    case 0x3b:
      // DCX SP
      // TODO
      break;

    case 0x3c:
      // INR A
      inr(&state->reg_a);
      break;

    case 0x3d:
      // DCR A
      dcr(&state->reg_a);
      break;

    case 0x3e:
      // MVI A
      mvi(state->mem[pc+1], &state->reg_a);
      break;

    case 0x3f:
      // CMC
      cmc(state);
      break;

    case 0x40:
      // MOV B,B

      break;

    case 0x41:
      // MOV B,C

      break;

    case 0x42:
      // MOV B,D

      break;

    case 0x43:
      // MOV B,E

      break;

    case 0x44:
      // MOV B,H

      break;

    case 0x45:
      // MOV B,L

      break;

    case 0x46:
      // MOV B,M

      break;

    case 0x47:
      // MOV B,A

      break;

    case 0x48:
      // MOV C,B

      break;

    case 0x49:
      // MOV C,C

      break;

    case 0x4a:
      // MOV C,D

      break;

    case 0x4b:
      // MOV C,E

      break;

    case 0x4c:
      // MOV C,H

      break;

    case 0x4d:
      // MOV C,L

      break;

    case 0x4e:
      // MOV C,M

      break;

    case 0x4f:
      // MOV C,A

      break;

    case 0x50:
      // MOV D,B

      break;

    case 0x51:
      // MOV D,C

      break;

    case 0x52:
      // MOV D,D

      break;

    case 0x53:
      // MOV D,E

      break;

    case 0x54:
      // MOV D,H

      break;

    case 0x55:
      // MOV D,L

      break;

    case 0x56:
      // MOV D,M

      break;

    case 0x57:
      // MOV D,A

      break;

    case 0x58:
      // MOV E,B

      break;

    case 0x59:
      // MOV E,C

      break;

    case 0x5a:
      // MOV E,D

      break;

    case 0x5b:
      // MOV E,E

      break;

    case 0x5c:
      // MOV E,H

      break;

    case 0x5d:
      // MOV E,L

      break;

    case 0x5e:
      // MOV E,M

      break;

    case 0x5f:
      // MOV E,A

      break;

    case 0x60:
      // MOV H,B

      break;

    case 0x61:
      // MOV H,C

      break;

    case 0x62:
      // MOV H,D

      break;

    case 0x63:
      // MOV H,E

      break;

    case 0x64:
      // MOV H,H

      break;

    case 0x65:
      // MOV H,L

      break;

    case 0x66:
      // MOV H,M

      break;

    case 0x67:
      // MOV H,A

      break;

    case 0x68:
      // MOV L,B

      break;

    case 0x69:
      // MOV L,C

      break;

    case 0x6a:
      // MOV L,D

      break;

    case 0x6b:
      // MOV L,E

      break;

    case 0x6c:
      // MOV L,H

      break;

    case 0x6d:
      // MOV L,L

      break;

    case 0x6e:
      // MOV L,M

      break;

    case 0x6f:
      // MOV L,A

      break;

    case 0x70:
      // MOV M,B

      break;

    case 0x71:
      // MOV M,C

      break;

    case 0x72:
      // MOV M,D

      break;

    case 0x73:
      // MOV M,E

      break;

    case 0x74:
      // MOV M,H

      break;

    case 0x75:
      // MOV M,L

      break;

    case 0x76:
      // HLT

      break;

    case 0x77:
      // MOV M,A

      break;

    case 0x78:
      // MOV A,B

      break;

    case 0x79:
      // MOV A,C

      break;

    case 0x7a:
      // MOV A,D

      break;

    case 0x7b:
      // MOV A,E

      break;

    case 0x7c:
      // MOV A,H

      break;

    case 0x7d:
      // MOV A,L

      break;

    case 0x7e:
      // MOV A,M

      break;

    case 0x7f:
      // MOV A,A

      break;

    case 0x80:
      // ADD B

      break;

    case 0x81:
      // ADD C

      break;

    case 0x82:
      // ADD D

      break;

    case 0x83:
      // ADD E

      break;

    case 0x84:
      // ADD H

      break;

    case 0x85:
      // ADD L

      break;

    case 0x86:
      // ADD M

      break;

    case 0x87:
      // ADD A

      break;

    case 0x88:
      // ADC B

      break;

    case 0x89:
      // ADC C

      break;

    case 0x8a:
      // ADC D

      break;

    case 0x8b:
      // ADC E

      break;

    case 0x8c:
      // ADC H

      break;

    case 0x8d:
      // ADC L

      break;

    case 0x8e:
      // ADC M

      break;

    case 0x8f:
      // ADC A

      break;

    case 0x90:
      // SUB B

      break;

    case 0x91:
      // SUB C

      break;

    case 0x92:
      // SUB D

      break;

    case 0x93:
      // SUB E

      break;

    case 0x94:
      // SUB H

      break;

    case 0x95:
      // SUB L

      break;

    case 0x96:
      // SUB M

      break;

    case 0x97:
      // SUB A

      break;

    case 0x98:
      // SBB B

      break;

    case 0x99:
      // SBB C

      break;

    case 0x9a:
      // SBB D

      break;

    case 0x9b:
      // SBB E

      break;

    case 0x9c:
      // SBB H

      break;

    case 0x9d:
      // SBB L

      break;

    case 0x9e:
      // SBB M

      break;

    case 0x9f:
      // SBB A

      break;

    case 0xa0:
      // ANA B

      break;

    case 0xa1:
      // ANA C

      break;

    case 0xa2:
      // ANA D

      break;

    case 0xa3:
      // ANA E

      break;

    case 0xa4:
      // ANA H

      break;

    case 0xa5:
      // ANA L

      break;

    case 0xa6:
      // ANA M

      break;

    case 0xa7:
      // ANA A

      break;

    case 0xa8:
      // XRA B

      break;

    case 0xa9:
      // XRA C

      break;

    case 0xaa:
      // XRA D

      break;

    case 0xab:
      // XRA E

      break;

    case 0xac:
      // XRA H

      break;

    case 0xad:
      // XRA L

      break;

    case 0xae:
      // XRA M

      break;

    case 0xaf:
      // XRA A

      break;

    case 0xb0:
      // ORA B

      break;

    case 0xb1:
      // ORA C

      break;

    case 0xb2:
      // ORA D

      break;

    case 0xb3:
      // ORA E

      break;

    case 0xb4:
      // ORA H

      break;

    case 0xb5:
      // ORA L

      break;

    case 0xb6:
      // ORA M

      break;

    case 0xb7:
      // ORA A

      break;

    case 0xb8:
      // CMP B

      break;

    case 0xb9:
      // CMP C

      break;

    case 0xba:
      // CMP D

      break;

    case 0xbb:
      // CMP E

      break;

    case 0xbc:
      // CMP H

      break;

    case 0xbd:
      // CMP L

      break;

    case 0xbe:
      // CMP M

      break;

    case 0xbf:
      // CMP A

      break;

    case 0xc0:
      // RNZ

      break;

    case 0xc1:
      // POP B

      break;

    case 0xc2:
      // JNZ

      break;

    case 0xc3:
      // JMP

      break;

    case 0xc4:
      // CNZ

      break;

    case 0xc5:
      // PUSH B

      break;

    case 0xc6:
      // ADI

      break;

    case 0xc7:
      // RST 0

      break;

    case 0xc8:
      // RZ

      break;

    case 0xc9:
      // RET

      break;

    case 0xca:
      // JZ

      break;

    case 0xcb:
      // NONE

      break;

    case 0xcc:
      // CZ

      break;

    case 0xcd:
      // CALL

      break;

    case 0xce:
      // ACI

      break;

    case 0xcf:
      // RST 1

      break;

    case 0xd0:
      // RNC

      break;

    case 0xd1:
      // POP D

      break;

    case 0xd2:
      // JNC

      break;

    case 0xd3:
      // OUT

      break;

    case 0xd4:
      // CNC

      break;

    case 0xd5:
      // PUSH

      break;

    case 0xd6:
      // SUI

      break;

    case 0xd7:
      // RST 2

      break;

    case 0xd8:
      // RC

      break;

    case 0xd9:
      // NONE

      break;

    case 0xda:
      // JC

      break;

    case 0xdb:
      // IN

      break;

    case 0xdc:
      // CC

      break;

    case 0xdd:
      // NONE

      break;

    case 0xde:
      // SBI

      break;

    case 0xdf:
      // RST 3

      break;

    case 0xe0:
      // RPO

      break;

    case 0xe1:
      // POP H

      break;

    case 0xe2:
      // JPO

      break;

    case 0xe3:
      // XTHL

      break;

    case 0xe4:
      // CPO

      break;

    case 0xe5:
      // PUSH H

      break;

    case 0xe6:
      // ANI

      break;

    case 0xe7:
      // RST 4

      break;

    case 0xe8:
      // RPE

      break;

    case 0xe9:
      // PCHL

      break;

    case 0xea:
      // JPE

      break;

    case 0xeb:
      // XCHG

      break;

    case 0xec:
      // CPE

      break;

    case 0xed:
      // NONE

      break;

    case 0xee:
      // XRI

      break;

    case 0xef:
      // RST 5

      break;

    case 0xf0:
      // RP

      break;

    case 0xf1:
      // POP PSW

      break;

    case 0xf2:
      // JP

      break;

    case 0xf3:
      // DI

      break;

    case 0xf4:
      // CP

      break;

    case 0xf5:
      // PUSH PSW

      break;

    case 0xf6:
      // ORI

      break;

    case 0xf7:
      // RST 6

      break;

    case 0xf8:
      // RM

      break;

    case 0xf9:
      // SPHL

      break;

    case 0xfa:
      // JM

      break;

    case 0xfb:
      // EI

      break;

    case 0xfc:
      // CM

      break;

    case 0xfd:
      // NONE

      break;

    case 0xfe:
      // CPI

      break;

    case 0xff:
      // RST 7

      break;
  }

  state->pc += op_code.size;
}

void init_state(ProcState *state) {
  state->reg_a=0x52;
  state->reg_b=0b11111111;
  state->reg_c=0b10101010;
  state->reg_d=0x10;
  state->reg_e=0x20;
  state->reg_h=0x30;
  state->reg_l=0x40;
  state->pc=0x777;
  state->sp=0x100;
  state->carry=0;
  state->aux_carry=0;
  state->zero=0;
  state->parity=0;
  state->sign=0;
  state->mem[0x100] = 0x88;
  state->mem[0x101] = 0x99;
}

int main(int argc, char const *argv[]) {
  ProcState state;
  init_state(&state);

  // Load Memory
  copy_to_mem(state, 0, sizeof(TEST_BYTES), TEST_BYTES);

  // Program Loop
  while (1) {
    update_state(&state);
  }

  return 0;
}
