#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"
#include "op_codes.h"
#include "state_util.h"
#include "instructions.h"
#include "state.h"
#include "io_devices.h"

//#define LOG_CPU
//#define DIAGNOSTIC

const int DISPLAY_WIDTH = 256;
const int DISPLAY_HEIGHT = 224;
const int VIDEO_BYTES = 7168; // (DISPLAY_WIDTH * DISPLAY_HEIGHT) / 8;
const int PIXEL_BYTES = 229376; // DISPLAY_WIDTH * DISPLAY_HEIGHT * 4;

void interrupt(unsigned char op_code, ProcState *state) {
  state->is_interrupted = 1;
  state->interrupt_instr = op_code;
}

void execute_instr(unsigned char op_code, ProcState *state) {
  switch (op_code) {

    case 0x00:
      // NOP
      nop(state);
      break;

    case 0x01:
      // LXI B
      lxi(&state->reg_b, &state->reg_c, state);
      break;

    case 0x02:
      // STAX B
      stax(state->reg_b, state->reg_c, state);
      break;

    case 0x03:
      // INX B
      inx(&state->reg_b, &state->reg_c, state);
      break;

    case 0x04:
      // INR B
      inr(&state->reg_b, state);
      break;

    case 0x05:
      // DCR B
      dcr(&state->reg_b, state);
      break;

    case 0x06:
      // MVI B
      mvi(&state->reg_b, state);
      break;

    case 0x07:
      // RLC
      rlc(state);
      break;

    case 0x08:
      // NONE
      unused(state);
      return;

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
      dcx(&state->reg_b, &state->reg_c, state);
      break;

    case 0x0c:
      // INR C
      inr(&state->reg_c, state);
      break;

    case 0x0d:
      // DCR C
      dcr(&state->reg_c, state);
      break;

    case 0x0e:
      // MVI C
      mvi(&state->reg_c, state);
      break;

    case 0x0f:
      // RRC
      rrc(state);
      break;

    case 0x10:
      // NONE
      unused(state);
      return;

    case 0x11:
      // LXI D
      lxi(&state->reg_d, &state->reg_e, state);
      break;

    case 0x12:
      // STAX D
      stax(state->reg_d, state->reg_e, state);
      break;

    case 0x13:
      // INX D
      inx(&state->reg_d, &state->reg_e, state);
      break;

    case 0x14:
      // INR D
      inr(&state->reg_d, state);
      break;

    case 0x15:
      // DCR D
      dcr(&state->reg_d, state);
      break;

    case 0x16:
      // MVI D
      mvi(&state->reg_d, state);
      break;

    case 0x17:
      // RAL
      ral(state);
      break;

    case 0x18:
      // NONE
      unused(state);
      return;

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
      dcx(&state->reg_d, &state->reg_e, state);
      break;

    case 0x1c:
      // INR E
      inr(&state->reg_e, state);
      break;

    case 0x1d:
      // DCR E
      dcr(&state->reg_e, state);
      break;

    case 0x1e:
      // MVI E
      mvi(&state->reg_e, state);
      break;

    case 0x1f:
      // RAR
      rar(state);
      break;

    case 0x20:
      // NONE
      unused(state);
      return;

    case 0x21:
      // LXI H
      lxi(&state->reg_h, &state->reg_l, state);
      break;

    case 0x22:
      // SHLD
      shld(state);
      break;

    case 0x23:
      // INX H
      inx(&state->reg_h, &state->reg_l, state);
      break;

    case 0x24:
      // INR H
      inr(&state->reg_h, state);
      break;

    case 0x25:
      // DCR H
      dcr(&state->reg_h, state);
      break;

    case 0x26:
      // MVI H
      mvi(&state->reg_h, state);
      break;

    case 0x27:
      // DAA
      daa(state);
      break;

    case 0x28:
      // NONE
      unused(state);
      return;

    case 0x29:
      // DAD H
      dad(state->reg_h, state->reg_l, state);
      break;

    case 0x2a:
      // LHLD
      lhld(state);
      break;

    case 0x2b:
      // DCX H
      dcx(&state->reg_h, &state->reg_l, state);
      break;

    case 0x2c:
      // INR L
      inr(&state->reg_l, state);
      break;

    case 0x2d:
      // DCR L
      dcr(&state->reg_l, state);
      break;

    case 0x2e:
      // MVI L
      mvi(&state->reg_l, state);
      break;

    case 0x2f:
      // CMA
      cma(state);
      break;

    case 0x30:
      // NONE
      unused(state);
      return;

    case 0x31:
      // LXI SP
      lxi_16(&state->sp, state);
      break;

    case 0x32:
      // STA
      sta(state);
      break;

    case 0x33:
      // INX SP
      inx_16(&state->sp, state);
      break;

    case 0x34:
      // INR M
      inr(get_mem_byte(state), state);
      break;

    case 0x35:
      // DCR M
      dcr(get_mem_byte(state), state);
      break;

    case 0x36:
      // MVI M
      mvi_m(get_mem_byte(state), state);
      break;

    case 0x37:
      // STC
      stc(state);
      break;

    case 0x38:
      // NONE
      unused(state);
      return;

    case 0x39:
      // DAD SP
      dad_16(&state->sp, state);
      break;

    case 0x3a:
      // LDA
      lda(state);
      break;

    case 0x3b:
      // DCX SP
      dcx_16(&state->sp, state);
      break;

    case 0x3c:
      // INR A
      inr(&state->reg_a, state);
      break;

    case 0x3d:
      // DCR A
      dcr(&state->reg_a, state);
      break;

    case 0x3e:
      // MVI A
      mvi(&state->reg_a, state);
      break;

    case 0x3f:
      // CMC
      cmc(state);
      break;

    case 0x40:
      // MOV B,B
      mov(state->reg_b, &state->reg_b, state);
      break;

    case 0x41:
      // MOV B,C
      mov(state->reg_c, &state->reg_b, state);
      break;

    case 0x42:
      // MOV B,D
      mov(state->reg_d, &state->reg_b, state);
      break;

    case 0x43:
      // MOV B,E
      mov(state->reg_e, &state->reg_b, state);
      break;

    case 0x44:
      // MOV B,H
      mov(state->reg_h, &state->reg_b, state);
      break;

    case 0x45:
      // MOV B,L
      mov(state->reg_l, &state->reg_b, state);
      break;

    case 0x46:
      // MOV B,M
      mov(*get_mem_byte(state), &state->reg_b, state);
      break;

    case 0x47:
      // MOV B,A
      mov(state->reg_a, &state->reg_b, state);
      break;

    case 0x48:
      // MOV C,B
      mov(state->reg_b, &state->reg_c, state);
      break;

    case 0x49:
      // MOV C,C
      mov(state->reg_c, &state->reg_c, state);
      break;

    case 0x4a:
      // MOV C,D
      mov(state->reg_d, &state->reg_c, state);
      break;

    case 0x4b:
      // MOV C,E
      mov(state->reg_e, &state->reg_c, state);
      break;

    case 0x4c:
      // MOV C,H
      mov(state->reg_h, &state->reg_c, state);
      break;

    case 0x4d:
      // MOV C,L
      mov(state->reg_l, &state->reg_c, state);
      break;

    case 0x4e:
      // MOV C,M
      mov(*get_mem_byte(state), &state->reg_c, state);
      break;

    case 0x4f:
      // MOV C,A
      mov(state->reg_a, &state->reg_c, state);
      break;

    case 0x50:
      // MOV D,B
      mov(state->reg_b, &state->reg_d, state);
      break;

    case 0x51:
      // MOV D,C
      mov(state->reg_c, &state->reg_d, state);
      break;

    case 0x52:
      // MOV D,D
      mov(state->reg_d, &state->reg_d, state);
      break;

    case 0x53:
      // MOV D,E
      mov(state->reg_e, &state->reg_d, state);
      break;

    case 0x54:
      // MOV D,H
      mov(state->reg_h, &state->reg_d, state);
      break;

    case 0x55:
      // MOV D,L
      mov(state->reg_l, &state->reg_d, state);
      break;

    case 0x56:
      // MOV D,M
      mov(*get_mem_byte(state), &state->reg_d, state);
      break;

    case 0x57:
      // MOV D,A
      mov(state->reg_a, &state->reg_d, state);
      break;

    case 0x58:
      // MOV E,B
      mov(state->reg_b, &state->reg_e, state);
      break;

    case 0x59:
      // MOV E,C
      mov(state->reg_c, &state->reg_e, state);
      break;

    case 0x5a:
      // MOV E,D
      mov(state->reg_d, &state->reg_e, state);
      break;

    case 0x5b:
      // MOV E,E
      mov(state->reg_e, &state->reg_e, state);
      break;

    case 0x5c:
      // MOV E,H
      mov(state->reg_h, &state->reg_e, state);
      break;

    case 0x5d:
      // MOV E,L
      mov(state->reg_l, &state->reg_e, state);
      break;

    case 0x5e:
      // MOV E,M
      mov(*get_mem_byte(state), &state->reg_e, state);
      break;

    case 0x5f:
      // MOV E,A
      mov(state->reg_a, &state->reg_e, state);
      break;

    case 0x60:
      // MOV H,B
      mov(state->reg_b, &state->reg_h, state);
      break;

    case 0x61:
      // MOV H,C
      mov(state->reg_c, &state->reg_h, state);
      break;

    case 0x62:
      // MOV H,D
      mov(state->reg_d, &state->reg_h, state);
      break;

    case 0x63:
      // MOV H,E
      mov(state->reg_e, &state->reg_h, state);
      break;

    case 0x64:
      // MOV H,H
      mov(state->reg_h, &state->reg_h, state);
      break;

    case 0x65:
      // MOV H,L
      mov(state->reg_l, &state->reg_h, state);
      break;

    case 0x66:
      // MOV H,M
      mov(*get_mem_byte(state), &state->reg_h, state);
      break;

    case 0x67:
      // MOV H,A
      mov(state->reg_a, &state->reg_h, state);
      break;

    case 0x68:
      // MOV L,B
      mov(state->reg_b, &state->reg_l, state);
      break;

    case 0x69:
      // MOV L,C
      mov(state->reg_c, &state->reg_l, state);
      break;

    case 0x6a:
      // MOV L,D
      mov(state->reg_d, &state->reg_l, state);
      break;

    case 0x6b:
      // MOV L,E
      mov(state->reg_e, &state->reg_l, state);
      break;

    case 0x6c:
      // MOV L,H
      mov(state->reg_h, &state->reg_l, state);
      break;

    case 0x6d:
      // MOV L,L
      mov(state->reg_l, &state->reg_l, state);
      break;

    case 0x6e:
      // MOV L,M
      mov(*get_mem_byte(state), &state->reg_l, state);
      break;

    case 0x6f:
      // MOV L,A
      mov(state->reg_a, &state->reg_l, state);
      break;

    case 0x70:
      // MOV M,B
      mov(state->reg_b, get_mem_byte(state), state);
      break;

    case 0x71:
      // MOV M,C
      mov(state->reg_c, get_mem_byte(state), state);
      break;

    case 0x72:
      // MOV M,D
      mov(state->reg_d, get_mem_byte(state), state);
      break;

    case 0x73:
      // MOV M,E
      mov(state->reg_e, get_mem_byte(state), state);
      break;

    case 0x74:
      // MOV M,H
      mov(state->reg_h, get_mem_byte(state), state);
      break;

    case 0x75:
      // MOV M,L
      mov(state->reg_l, get_mem_byte(state), state);
      break;

    case 0x76:
      // HLT
      hlt(state);
      break;

    case 0x77:
      // MOV M,A
      mov(state->reg_a, get_mem_byte(state), state);
      break;

    case 0x78:
      // MOV A,B
      mov(state->reg_b, &state->reg_a, state);
      break;

    case 0x79:
      // MOV A,C
      mov(state->reg_c, &state->reg_a, state);
      break;

    case 0x7a:
      // MOV A,D
      mov(state->reg_d, &state->reg_a, state);
      break;

    case 0x7b:
      // MOV A,E
      mov(state->reg_e, &state->reg_a, state);
      break;

    case 0x7c:
      // MOV A,H
      mov(state->reg_h, &state->reg_a, state);
      break;

    case 0x7d:
      // MOV A,L
      mov(state->reg_l, &state->reg_a, state);
      break;

    case 0x7e:
      // MOV A,M
      mov(*get_mem_byte(state), &state->reg_a, state);
      break;

    case 0x7f:
      // MOV A,A
      mov(state->reg_a, &state->reg_a, state);
      break;

    case 0x80:
      // ADD B
      add(state->reg_b, state);
      break;

    case 0x81:
      // ADD C
      add(state->reg_c, state);
      break;

    case 0x82:
      // ADD D
      add(state->reg_d, state);
      break;

    case 0x83:
      // ADD E
      add(state->reg_e, state);
      break;

    case 0x84:
      // ADD H
      add(state->reg_h, state);
      break;

    case 0x85:
      // ADD L
      add(state->reg_l, state);
      break;

    case 0x86:
      // ADD M
      add(*get_mem_byte(state), state);
      break;

    case 0x87:
      // ADD A
      add(state->reg_a, state);
      break;

    case 0x88:
      // ADC B
      adc(state->reg_b, state);
      break;

    case 0x89:
      // ADC C
      adc(state->reg_c, state);
      break;

    case 0x8a:
      // ADC D
      adc(state->reg_d, state);
      break;

    case 0x8b:
      // ADC E
      adc(state->reg_e, state);
      break;

    case 0x8c:
      // ADC H
      adc(state->reg_h, state);
      break;

    case 0x8d:
      // ADC L
      adc(state->reg_l, state);
      break;

    case 0x8e:
      // ADC M
      adc(*get_mem_byte(state), state);
      break;

    case 0x8f:
      // ADC A
      adc(state->reg_a, state);
      break;

    case 0x90:
      // SUB B
      sub(state->reg_b, state);
      break;

    case 0x91:
      // SUB C
      sub(state->reg_c, state);
      break;

    case 0x92:
      // SUB D
      sub(state->reg_d, state);
      break;

    case 0x93:
      // SUB E
      sub(state->reg_e, state);
      break;

    case 0x94:
      // SUB H
      sub(state->reg_h, state);
      break;

    case 0x95:
      // SUB L
      sub(state->reg_l, state);
      break;

    case 0x96:
      // SUB M
      sub(*get_mem_byte(state), state);
      break;

    case 0x97:
      // SUB A
      sub(state->reg_a, state);
      break;

    case 0x98:
      // SBB B
      sbb(state->reg_b, state);
      break;

    case 0x99:
      // SBB C
      sbb(state->reg_c, state);
      break;

    case 0x9a:
      // SBB D
      sbb(state->reg_d, state);
      break;

    case 0x9b:
      // SBB E
      sbb(state->reg_e, state);
      break;

    case 0x9c:
      // SBB H
      sbb(state->reg_h, state);
      break;

    case 0x9d:
      // SBB L
      sbb(state->reg_l, state);
      break;

    case 0x9e:
      // SBB M
      sbb(*get_mem_byte(state), state);
      break;

    case 0x9f:
      // SBB A
      sbb(state->reg_a, state);
      break;

    case 0xa0:
      // ANA B
      ana(state->reg_b, state);
      break;

    case 0xa1:
      // ANA C
      ana(state->reg_c, state);
      break;

    case 0xa2:
      // ANA D
      ana(state->reg_d, state);
      break;

    case 0xa3:
      // ANA E
      ana(state->reg_e, state);
      break;

    case 0xa4:
      // ANA H
      ana(state->reg_h, state);
      break;

    case 0xa5:
      // ANA L
      ana(state->reg_l, state);
      break;

    case 0xa6:
      // ANA M
      ana(*get_mem_byte(state), state);
      break;

    case 0xa7:
      // ANA A
      ana(state->reg_a, state);
      break;

    case 0xa8:
      // XRA B
      xra(state->reg_b, state);
      break;

    case 0xa9:
      // XRA C
      xra(state->reg_c, state);
      break;

    case 0xaa:
      // XRA D
      xra(state->reg_d, state);
      break;

    case 0xab:
      // XRA E
      xra(state->reg_e, state);
      break;

    case 0xac:
      // XRA H
      xra(state->reg_h, state);
      break;

    case 0xad:
      // XRA L
      xra(state->reg_l, state);
      break;

    case 0xae:
      // XRA M
      xra(*get_mem_byte(state), state);
      break;

    case 0xaf:
      // XRA A
      xra(state->reg_a, state);
      break;

    case 0xb0:
      // ORA B
      ora(state->reg_b, state);
      break;

    case 0xb1:
      // ORA C
      ora(state->reg_c, state);
      break;

    case 0xb2:
      // ORA D
      ora(state->reg_d, state);
      break;

    case 0xb3:
      // ORA E
      ora(state->reg_e, state);
      break;

    case 0xb4:
      // ORA H
      ora(state->reg_h, state);
      break;

    case 0xb5:
      // ORA L
      ora(state->reg_l, state);
      break;

    case 0xb6:
      // ORA M
      ora(*get_mem_byte(state), state);
      break;

    case 0xb7:
      // ORA A
      ora(state->reg_a, state);
      break;

    case 0xb8:
      // CMP B
      cmp(state->reg_b, state);
      break;

    case 0xb9:
      // CMP C
      cmp(state->reg_c, state);
      break;

    case 0xba:
      // CMP D
      cmp(state->reg_d, state);
      break;

    case 0xbb:
      // CMP E
      cmp(state->reg_e, state);
      break;

    case 0xbc:
      // CMP H
      cmp(state->reg_h, state);
      break;

    case 0xbd:
      // CMP L
      cmp(state->reg_l, state);
      break;

    case 0xbe:
      // CMP M
      cmp(*get_mem_byte(state), state);
      break;

    case 0xbf:
      // CMP A
      cmp(state->reg_a, state);
      break;

    case 0xc0:
      // RNZ
      rnz(state);
      break;

    case 0xc1:
      // POP B
      pop(&state->reg_b, &state->reg_c, state);
      break;

    case 0xc2:
      // JNZ
      jnz(state);
      break;

    case 0xc3:
      // JMP
      jmp(state);
      break;

    case 0xc4:
      // CNZ
      cnz(state);
      break;

    case 0xc5:
      // PUSH B
      push(state->reg_b, state->reg_c, state);
      break;

    case 0xc6:
      // ADI
      adi(state);
      break;

    case 0xc7:
      // RST 0
      rst(0, state);
      break;

    case 0xc8:
      // RZ
      rz(state);
      break;

    case 0xc9:
      // RET
      ret(state);
      break;

    case 0xca:
      // JZ
      jz(state);
      break;

    case 0xcb:
      // NONE
      unused(state);
      return;

    case 0xcc:
      // CZ
      cz(state);
      break;

    case 0xcd:
      // CALL
      call(state);
      break;

    case 0xce:
      // ACI
      aci(state);
      break;

    case 0xcf:
      // RST 1
      rst(1, state);
      break;

    case 0xd0:
      // RNC
      rnc(state);
      break;

    case 0xd1:
      // POP D
      pop(&state->reg_d, &state->reg_e, state);
      break;

    case 0xd2:
      // JNC
      jnc(state);
      break;

    case 0xd3:
      // OUT
      out(state);
      break;

    case 0xd4:
      // CNC
      cnc(state);
      break;

    case 0xd5:
      // PUSH D
      push(state->reg_d, state->reg_e, state);
      break;

    case 0xd6:
      // SUI
      sui(state);
      break;

    case 0xd7:
      // RST 2
      rst(2, state);
      break;

    case 0xd8:
      // RC
      rc(state);
      break;

    case 0xd9:
      // NONE
      unused(state);
      return;

    case 0xda:
      // JC
      jc(state);
      break;

    case 0xdb:
      // IN
      in(state);
      break;

    case 0xdc:
      // CC
      cc(state);
      break;

    case 0xdd:
      // NONE
      unused(state);
      return;

    case 0xde:
      // SBI
      sbi(state);
      break;

    case 0xdf:
      // RST 3
      rst(3, state);
      break;

    case 0xe0:
      // RPO
      rpo(state);
      break;

    case 0xe1:
      // POP H
      pop(&state->reg_h, &state->reg_l, state);
      break;

    case 0xe2:
      // JPO
      jpo(state);
      break;

    case 0xe3:
      // XTHL
      xthl(state);
      break;

    case 0xe4:
      // CPO
      cpo(state);
      break;

    case 0xe5:
      // PUSH H
      push(state->reg_h, state->reg_l, state);
      break;

    case 0xe6:
      // ANI
      ani(state);
      break;

    case 0xe7:
      // RST 4
      rst(4, state);
      break;

    case 0xe8:
      // RPE
      rpe(state);
      break;

    case 0xe9:
      // PCHL
      pchl(state);
      break;

    case 0xea:
      // JPE
      jpe(state);
      break;

    case 0xeb:
      // XCHG
      xchg(state);
      break;

    case 0xec:
      // CPE
      cpe(state);
      break;

    case 0xed:
      // NONE
      unused(state);
      return;

    case 0xee:
      // XRI
      xri(state);
      break;

    case 0xef:
      // RST 5
      rst(5, state);
      break;

    case 0xf0:
      // RP
      rp(state);
      break;

    case 0xf1:
      // POP PSW
      pop_psw(state);
      break;

    case 0xf2:
      // JP
      jp(state);
      break;

    case 0xf3:
      // DI
      di(state);
      break;

    case 0xf4:
      // CP
      cp(state);
      break;

    case 0xf5:
      // PUSH PSW
      push_psw(state);
      break;

    case 0xf6:
      // ORI
      ori(state);
      break;

    case 0xf7:
      // RST 6
      rst(6, state);
      break;

    case 0xf8:
      // RM
      rm(state);
      break;

    case 0xf9:
      // SPHL
      sphl(state);
      break;

    case 0xfa:
      // JM
      jm(state);
      break;

    case 0xfb:
      // EI
      ei(state);
      break;

    case 0xfc:
      // CM
      cm(state);
      break;

    case 0xfd:
      // NONE
      unused(state);
      return;

    case 0xfe:
      // CPI
      cpi(state);
      break;

    case 0xff:
      // RST 7
      rst(7, state);
      break;
  }
}

void update_state(ProcState *state) {
  OpCode op_code = OP_CODES[state->mem[state->pc]];

#ifdef LOG_CPU

  printf("%4x: ", state->pc);

  switch (op_code.size) {
    case 1:
      printf("%s", op_code.name);
      break;
    case 2:
      printf("%s,0x%x", op_code.name, state->mem[state->pc+1]);
      break;
    case 3:
      printf("%s 0x%x,0x%x", op_code.name, state->mem[state->pc+2], state->mem[state->pc+1]);
      break;
  }

  printf("\n");

#endif

  execute_instr(op_code.code, state);

  if (state->is_interrupted) {
    state->is_interrupted = 0;
    state->inte = 0;
    execute_instr(state->interrupt_instr, state);
  }
}

unsigned char init_input_func_stub() {
  printf("WARN: Attempt to read data from unmapped input device\n");
  return 0;
}

void init_output_func_stub(unsigned char data) {
  printf("WARN: Attempt to write data to unmapped output device\n");
}

void init_state(ProcState *state) {
  state->reg_a=0x00;
  state->reg_b=0x00;
  state->reg_c=0x00;
  state->reg_d=0x00;
  state->reg_e=0x00;
  state->reg_h=0x00;
  state->reg_l=0x00;
  state->pc=0x0000;
  state->sp=0x0000;
  state->carry=0;
  state->aux_carry=0;
  state->zero=0;
  state->parity=0;
  state->sign=0;
  state->inte=1;
  state->is_interrupted=0;
  for (int i = 0; i < 256; i++) {
    state->inputs[i] = init_input_func_stub;
    state->outputs[i] = init_output_func_stub;
  }
}

int read_file_to_mem(const char *filename, const int offset, ProcState *state) {
  printf("%s\n", filename);

  FILE *file;
  unsigned long filesize;

  file = fopen(filename, "rb");

  if (file == NULL) {
    printf("Failed to open file\n");
    return 0;
  }

  fseek(file, 0, SEEK_END);
	filesize=ftell(file);
	fseek(file, 0, SEEK_SET);

  if (filesize + offset <= sizeof state->mem) {
    printf("Loading %ld bytes starting at memory address 0x%x\n", filesize, offset);
  } else {
    printf("Failed to open file - file too large");
    return 0;
  }

  unsigned char *buf = &state->mem[offset];

  fread(buf, filesize, 1, file);
	fclose(file);
  return 1;
}

int load_diagnostic(const char *path, ProcState *state) {
  const int offset = 0x100;
  return read_file_to_mem(path, offset, state);
}

int load_space_invaders(const char *dir, ProcState *state) {
  size_t path_length = (strlen(dir)) + 12; // length of `/invaders.x`
  char part_1[path_length];
  char part_2[path_length];
  char part_3[path_length];
  char part_4[path_length];
  snprintf(part_1, path_length, "%s/invaders.h", dir);
  snprintf(part_2, path_length, "%s/invaders.g", dir);
  snprintf(part_3, path_length, "%s/invaders.f", dir);
  snprintf(part_4, path_length, "%s/invaders.e", dir);
  if (!read_file_to_mem(part_1, 0x0000, state)) return 0;
  if (!read_file_to_mem(part_2, 0x0800, state)) return 0;
  if (!read_file_to_mem(part_3, 0x1000, state)) return 0;
  if (!read_file_to_mem(part_4, 0x1800, state)) return 0;
  return 1;
}

void generate_pixels(unsigned char *pixels, unsigned char *video_memory) {
  for (int i = 0; i < VIDEO_BYTES; i++) {
    for (int j = 7; j >= 0; j--) {
      unsigned char on = ((video_memory[i] >> j) & 1) ? 0xff : 0;
      int k = (i << 5) + (j << 2);
      pixels[k] = on;
      pixels[k+1] = on;
      pixels[k+2] = on;
      pixels[k+3] = SDL_ALPHA_OPAQUE;
    }
  } 
}

int main(int argc, char const *argv[]) {
  ProcState state;
  init_state(&state);
  register_io_devices(&state);

  if (argc == 2) {
    int success = load_space_invaders(argv[1], &state);
    if (!success) {
      return 1;
    }
  } else {
    printf("Invalid argument count\n");
    return 1;
  }

#ifdef DIAGNOSTIC
  // Ignore DAA tests in diagnostic binary
  state.mem[0x59c] = 0xc3; // JMP    
  state.mem[0x59d] = 0xc2;    
  state.mem[0x59e] = 0x05;
#endif

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
    "Emulator Window",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    DISPLAY_WIDTH,
    DISPLAY_HEIGHT,
    SDL_WINDOW_OPENGL
  );

  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
  );

  SDL_Texture* texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    DISPLAY_WIDTH, 
    DISPLAY_HEIGHT
  );

  unsigned char pixels[PIXEL_BYTES];
  memset(pixels, 0, PIXEL_BYTES);

  SDL_Event e;

  // Screen refresh is 60 hz, 
  //but there's an interrupt twice per refresh
  Uint32 screen_refresh_timeout = SDL_GetTicks() + (1000 / 120);
  int screen_refresh_halfway = 0;

  // Program Loop
  while (1) {
    update_state(&state);
    usleep(2);

    if (SDL_TICKS_PASSED(SDL_GetTicks(), screen_refresh_timeout)) {
      // RST 1 when "halfway", RST 2 at "end of screen"
      unsigned char interrupt_instr = screen_refresh_halfway ? 0xcf : 0xd7;
      interrupt(interrupt_instr, &state);
      screen_refresh_halfway = ~screen_refresh_halfway;
      screen_refresh_timeout = SDL_GetTicks() + (1000 / 120);

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      generate_pixels(&pixels[0], &state.mem[0x2400]);

      SDL_UpdateTexture(
        texture,
        NULL,
        &pixels[0],
        DISPLAY_WIDTH * 4
      );

      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);

      // Handle SDL Events
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          SDL_Log("Program quit after %i ticks", e.quit.timestamp);
          SDL_Quit();
          return 0;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_SPACE:
              p1_shot_on();
              break;
            case SDLK_RETURN:
              p1_start_on();
              break;
            case SDLK_LEFT:
              p1_left_on();
              break;
            case SDLK_RIGHT:
              p1_right_on();
              break;
            case SDLK_t:
              tilt_switch_on();
              break;
            case SDLK_c:
              coin_switch_on();
              break;
          }
        } else if (e.type == SDL_KEYUP) {
          switch (e.key.keysym.sym) {
            case SDLK_SPACE:
              p1_shot_off();
              break;
            case SDLK_RETURN:
              p1_start_off();
              break;
            case SDLK_LEFT:
              p1_left_off();
              break;
            case SDLK_RIGHT:
              p1_right_off();
              break;
            case SDLK_t:
              tilt_switch_off();
              break;
            case SDLK_c:
              coin_switch_off();
              break;
          }
        }
      }
    }
  }
}
