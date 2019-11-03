#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"
#include "op_codes.h"
#include "state_util.h"
#include "instructions.h"
#include "state.h"
#include "io_devices.h"

// #define LOG_CPU
// #define DIAGNOSTIC

// Screen is rotated 90 degress in the window from how it's represented in the game's code
// so usually the width will be used as the height and vice versa.
const int DISPLAY_WIDTH = 256; 
const int DISPLAY_HEIGHT = 224;
const int VIDEO_BYTES = 7168; // (DISPLAY_WIDTH * DISPLAY_HEIGHT) / 8;
const int PIXEL_BYTES = 229376; // DISPLAY_WIDTH * DISPLAY_HEIGHT * 4;

void interrupt(unsigned char op_code, State8080 *state) {
  state->is_interrupted = 1;
  state->interrupt_instr = op_code;
}

int execute_instr(unsigned char op_code, State8080 *state) {
  switch (op_code) {

    case 0x00:
      // NOP
      return nop(state);
      
    case 0x01:
      // LXI B
      return lxi(&state->reg_b, &state->reg_c, state);
      
    case 0x02:
      // STAX B
      return stax(state->reg_b, state->reg_c, state);
      
    case 0x03:
      // INX B
      return inx(&state->reg_b, &state->reg_c, state);
      
    case 0x04:
      // INR B
      return inr(&state->reg_b, state);
      
    case 0x05:
      // DCR B
      return dcr(&state->reg_b, state);
      
    case 0x06:
      // MVI B
      return mvi(&state->reg_b, state);
      
    case 0x07:
      // RLC
      return rlc(state);
      
    case 0x08:
      // NONE
      return unused(state);
      
    case 0x09:
      // DAD B
      return dad(state->reg_b, state->reg_c, state);
      
    case 0x0a:
      // LDAX B
      return ldax(state->reg_b, state->reg_c, state);
      
    case 0x0b:
      // DCX B
      return dcx(&state->reg_b, &state->reg_c, state);
      
    case 0x0c:
      // INR C
      return inr(&state->reg_c, state);
      
    case 0x0d:
      // DCR C
      return dcr(&state->reg_c, state);
      
    case 0x0e:
      // MVI C
      return mvi(&state->reg_c, state);
      
    case 0x0f:
      // RRC
      return rrc(state);
      
    case 0x10:
      // NONE
      return unused(state);
      
    case 0x11:
      // LXI D
      return lxi(&state->reg_d, &state->reg_e, state);
      
    case 0x12:
      // STAX D
      return stax(state->reg_d, state->reg_e, state);
      
    case 0x13:
      // INX D
      return inx(&state->reg_d, &state->reg_e, state);
      
    case 0x14:
      // INR D
      return inr(&state->reg_d, state);
      
    case 0x15:
      // DCR D
      return dcr(&state->reg_d, state);
      
    case 0x16:
      // MVI D
      return mvi(&state->reg_d, state);
      
    case 0x17:
      // RAL
      return ral(state);
      
    case 0x18:
      // NONE
      return unused(state);      

    case 0x19:
      // DAD D
      return dad(state->reg_d, state->reg_e, state);
      
    case 0x1a:
      // LDAX D
      return ldax(state->reg_d, state->reg_e, state);
      
    case 0x1b:
      // DCX D
      return dcx(&state->reg_d, &state->reg_e, state);
      
    case 0x1c:
      // INR E
      return inr(&state->reg_e, state);
      
    case 0x1d:
      // DCR E
      return dcr(&state->reg_e, state);
      
    case 0x1e:
      // MVI E
      return mvi(&state->reg_e, state);
      
    case 0x1f:
      // RAR
      return rar(state);
      
    case 0x20:
      // NONE
      return unused(state);
      
    case 0x21:
      // LXI H
      return lxi(&state->reg_h, &state->reg_l, state);
      
    case 0x22:
      // SHLD
      return shld(state);
      
    case 0x23:
      // INX H
      return inx(&state->reg_h, &state->reg_l, state);
      
    case 0x24:
      // INR H
      return inr(&state->reg_h, state);
      
    case 0x25:
      // DCR H
      return dcr(&state->reg_h, state);
      
    case 0x26:
      // MVI H
      return mvi(&state->reg_h, state);
      
    case 0x27:
      // DAA
      return daa(state);
      
    case 0x28:
      // NONE
      return unused(state);
      
    case 0x29:
      // DAD H
      return dad(state->reg_h, state->reg_l, state);
      
    case 0x2a:
      // LHLD
      return lhld(state);
      
    case 0x2b:
      // DCX H
      return dcx(&state->reg_h, &state->reg_l, state);
      
    case 0x2c:
      // INR L
      return inr(&state->reg_l, state);
      
    case 0x2d:
      // DCR L
      return dcr(&state->reg_l, state);
      
    case 0x2e:
      // MVI L
      return mvi(&state->reg_l, state);
      
    case 0x2f:
      // CMA
      return cma(state);
      
    case 0x30:
      // NONE
      return unused(state);

    case 0x31:
      // LXI SP
      return lxi_16(&state->sp, state);
      
    case 0x32:
      // STA
      return sta(state);
      
    case 0x33:
      // INX SP
      return inx_16(&state->sp, state);
      
    case 0x34:
      // INR M
      return inr(get_mem_byte(state), state);
      
    case 0x35:
      // DCR M
      return dcr(get_mem_byte(state), state);
      
    case 0x36:
      // MVI M
      return mvi_m(get_mem_byte(state), state);
      
    case 0x37:
      // STC
      return stc(state);
      
    case 0x38:
      // NONE
      return unused(state);
      
    case 0x39:
      // DAD SP
      return dad_16(&state->sp, state);
      
    case 0x3a:
      // LDA
      return lda(state);
      
    case 0x3b:
      // DCX SP
      return dcx_16(&state->sp, state);
      
    case 0x3c:
      // INR A
      return inr(&state->reg_a, state);
      
    case 0x3d:
      // DCR A
      return dcr(&state->reg_a, state);
      
    case 0x3e:
      // MVI A
      return mvi(&state->reg_a, state);
      
    case 0x3f:
      // CMC
      return cmc(state);
      
    case 0x40:
      // MOV B,B
      return mov(state->reg_b, &state->reg_b, state);
      
    case 0x41:
      // MOV B,C
      return mov(state->reg_c, &state->reg_b, state);
      
    case 0x42:
      // MOV B,D
      return mov(state->reg_d, &state->reg_b, state);
      
    case 0x43:
      // MOV B,E
      return mov(state->reg_e, &state->reg_b, state);
      
    case 0x44:
      // MOV B,H
      return mov(state->reg_h, &state->reg_b, state);
      
    case 0x45:
      // MOV B,L
      return mov(state->reg_l, &state->reg_b, state);
      
    case 0x46:
      // MOV B,M
      return mov(*get_mem_byte(state), &state->reg_b, state);
      
    case 0x47:
      // MOV B,A
      return mov(state->reg_a, &state->reg_b, state);
      
    case 0x48:
      // MOV C,B
      return mov(state->reg_b, &state->reg_c, state);
      
    case 0x49:
      // MOV C,C
      return mov(state->reg_c, &state->reg_c, state);
      
    case 0x4a:
      // MOV C,D
      return mov(state->reg_d, &state->reg_c, state);
      
    case 0x4b:
      // MOV C,E
      return mov(state->reg_e, &state->reg_c, state);
      
    case 0x4c:
      // MOV C,H
      return mov(state->reg_h, &state->reg_c, state);
      
    case 0x4d:
      // MOV C,L
      return mov(state->reg_l, &state->reg_c, state);
      
    case 0x4e:
      // MOV C,M
      return mov(*get_mem_byte(state), &state->reg_c, state);
      
    case 0x4f:
      // MOV C,A
      return mov(state->reg_a, &state->reg_c, state);
      
    case 0x50:
      // MOV D,B
      return mov(state->reg_b, &state->reg_d, state);
      
    case 0x51:
      // MOV D,C
      return mov(state->reg_c, &state->reg_d, state);
      
    case 0x52:
      // MOV D,D
      return mov(state->reg_d, &state->reg_d, state);
      
    case 0x53:
      // MOV D,E
      return mov(state->reg_e, &state->reg_d, state);
      
    case 0x54:
      // MOV D,H
      return mov(state->reg_h, &state->reg_d, state);
      
    case 0x55:
      // MOV D,L
      return mov(state->reg_l, &state->reg_d, state);
      
    case 0x56:
      // MOV D,M
      return mov(*get_mem_byte(state), &state->reg_d, state);
      
    case 0x57:
      // MOV D,A
      return mov(state->reg_a, &state->reg_d, state);
      
    case 0x58:
      // MOV E,B
      return mov(state->reg_b, &state->reg_e, state);
      
    case 0x59:
      // MOV E,C
      return mov(state->reg_c, &state->reg_e, state);
      
    case 0x5a:
      // MOV E,D
      return mov(state->reg_d, &state->reg_e, state);
      
    case 0x5b:
      // MOV E,E
      return mov(state->reg_e, &state->reg_e, state);
      
    case 0x5c:
      // MOV E,H
      return mov(state->reg_h, &state->reg_e, state);
      
    case 0x5d:
      // MOV E,L
      return mov(state->reg_l, &state->reg_e, state);
      
    case 0x5e:
      // MOV E,M
      return mov(*get_mem_byte(state), &state->reg_e, state);
      
    case 0x5f:
      // MOV E,A
      return mov(state->reg_a, &state->reg_e, state);
      
    case 0x60:
      // MOV H,B
      return mov(state->reg_b, &state->reg_h, state);
      
    case 0x61:
      // MOV H,C
      return mov(state->reg_c, &state->reg_h, state);
      
    case 0x62:
      // MOV H,D
      return mov(state->reg_d, &state->reg_h, state);
      
    case 0x63:
      // MOV H,E
      return mov(state->reg_e, &state->reg_h, state);
      
    case 0x64:
      // MOV H,H
      return mov(state->reg_h, &state->reg_h, state);
      
    case 0x65:
      // MOV H,L
      return mov(state->reg_l, &state->reg_h, state);
      
    case 0x66:
      // MOV H,M
      return mov(*get_mem_byte(state), &state->reg_h, state);
      
    case 0x67:
      // MOV H,A
      return mov(state->reg_a, &state->reg_h, state);
      
    case 0x68:
      // MOV L,B
      return mov(state->reg_b, &state->reg_l, state);
      
    case 0x69:
      // MOV L,C
      return mov(state->reg_c, &state->reg_l, state);
      
    case 0x6a:
      // MOV L,D
      return mov(state->reg_d, &state->reg_l, state);
      
    case 0x6b:
      // MOV L,E
      return mov(state->reg_e, &state->reg_l, state);
      
    case 0x6c:
      // MOV L,H
      return mov(state->reg_h, &state->reg_l, state);
      
    case 0x6d:
      // MOV L,L
      return mov(state->reg_l, &state->reg_l, state);
      
    case 0x6e:
      // MOV L,M
      return mov(*get_mem_byte(state), &state->reg_l, state);
      
    case 0x6f:
      // MOV L,A
      return mov(state->reg_a, &state->reg_l, state);
      
    case 0x70:
      // MOV M,B
      return mov(state->reg_b, get_mem_byte(state), state);
      
    case 0x71:
      // MOV M,C
      return mov(state->reg_c, get_mem_byte(state), state);
      
    case 0x72:
      // MOV M,D
      return mov(state->reg_d, get_mem_byte(state), state);
      
    case 0x73:
      // MOV M,E
      return mov(state->reg_e, get_mem_byte(state), state);
      
    case 0x74:
      // MOV M,H
      return mov(state->reg_h, get_mem_byte(state), state);
      
    case 0x75:
      // MOV M,L
      return mov(state->reg_l, get_mem_byte(state), state);
      
    case 0x76:
      // HLT
      return hlt(state);
      
    case 0x77:
      // MOV M,A
      return mov(state->reg_a, get_mem_byte(state), state);
      
    case 0x78:
      // MOV A,B
      return mov(state->reg_b, &state->reg_a, state);
      
    case 0x79:
      // MOV A,C
      return mov(state->reg_c, &state->reg_a, state);
      
    case 0x7a:
      // MOV A,D
      return mov(state->reg_d, &state->reg_a, state);
      
    case 0x7b:
      // MOV A,E
      return mov(state->reg_e, &state->reg_a, state);
      
    case 0x7c:
      // MOV A,H
      return mov(state->reg_h, &state->reg_a, state);
      
    case 0x7d:
      // MOV A,L
      return mov(state->reg_l, &state->reg_a, state);
      
    case 0x7e:
      // MOV A,M
      return mov(*get_mem_byte(state), &state->reg_a, state);
      
    case 0x7f:
      // MOV A,A
      return mov(state->reg_a, &state->reg_a, state);
      
    case 0x80:
      // ADD B
      return add(state->reg_b, state);
      
    case 0x81:
      // ADD C
      return add(state->reg_c, state);
      
    case 0x82:
      // ADD D
      return add(state->reg_d, state);
      
    case 0x83:
      // ADD E
      return add(state->reg_e, state);
      
    case 0x84:
      // ADD H
      return add(state->reg_h, state);
      
    case 0x85:
      // ADD L
      return add(state->reg_l, state);
      
    case 0x86:
      // ADD M
      return add(*get_mem_byte(state), state);
      
    case 0x87:
      // ADD A
      return add(state->reg_a, state);
      
    case 0x88:
      // ADC B
      return adc(state->reg_b, state);
      
    case 0x89:
      // ADC C
      return adc(state->reg_c, state);
      
    case 0x8a:
      // ADC D
      return adc(state->reg_d, state);
      
    case 0x8b:
      // ADC E
      return adc(state->reg_e, state);
      
    case 0x8c:
      // ADC H
      return adc(state->reg_h, state);
      
    case 0x8d:
      // ADC L
      return adc(state->reg_l, state);
      
    case 0x8e:
      // ADC M
      return adc(*get_mem_byte(state), state);
      
    case 0x8f:
      // ADC A
      return adc(state->reg_a, state);
      
    case 0x90:
      // SUB B
      return sub(state->reg_b, state);
      
    case 0x91:
      // SUB C
      return sub(state->reg_c, state);
      
    case 0x92:
      // SUB D
      return sub(state->reg_d, state);
      
    case 0x93:
      // SUB E
      return sub(state->reg_e, state);
      
    case 0x94:
      // SUB H
      return sub(state->reg_h, state);
      
    case 0x95:
      // SUB L
      return sub(state->reg_l, state);
      
    case 0x96:
      // SUB M
      return sub(*get_mem_byte(state), state);
      
    case 0x97:
      // SUB A
      return sub(state->reg_a, state);
      
    case 0x98:
      // SBB B
      return sbb(state->reg_b, state);
      
    case 0x99:
      // SBB C
      return sbb(state->reg_c, state);
      
    case 0x9a:
      // SBB D
      return sbb(state->reg_d, state);
      
    case 0x9b:
      // SBB E
      return sbb(state->reg_e, state);
      
    case 0x9c:
      // SBB H
      return sbb(state->reg_h, state);
      
    case 0x9d:
      // SBB L
      return sbb(state->reg_l, state);
      
    case 0x9e:
      // SBB M
      return sbb(*get_mem_byte(state), state);
      
    case 0x9f:
      // SBB A
      return sbb(state->reg_a, state);
      
    case 0xa0:
      // ANA B
      return ana(state->reg_b, state);
      
    case 0xa1:
      // ANA C
      return ana(state->reg_c, state);
      
    case 0xa2:
      // ANA D
      return ana(state->reg_d, state);
      
    case 0xa3:
      // ANA E
      return ana(state->reg_e, state);
      
    case 0xa4:
      // ANA H
      return ana(state->reg_h, state);
      
    case 0xa5:
      // ANA L
      return ana(state->reg_l, state);
      
    case 0xa6:
      // ANA M
      return ana(*get_mem_byte(state), state);

    case 0xa7:
      // ANA A
      return ana(state->reg_a, state);
      
    case 0xa8:
      // XRA B
      return xra(state->reg_b, state);
      
    case 0xa9:
      // XRA C
      return xra(state->reg_c, state);
      
    case 0xaa:
      // XRA D
      return xra(state->reg_d, state);
      
    case 0xab:
      // XRA E
      return xra(state->reg_e, state);
      
    case 0xac:
      // XRA H
      return xra(state->reg_h, state);
      
    case 0xad:
      // XRA L
      return xra(state->reg_l, state);
      
    case 0xae:
      // XRA M
      return xra(*get_mem_byte(state), state);
      
    case 0xaf:
      // XRA A
      return xra(state->reg_a, state);
      
    case 0xb0:
      // ORA B
      return ora(state->reg_b, state);
      
    case 0xb1:
      // ORA C
      return ora(state->reg_c, state);
      
    case 0xb2:
      // ORA D
      return ora(state->reg_d, state);
      
    case 0xb3:
      // ORA E
      return ora(state->reg_e, state);

    case 0xb4:
      // ORA H
      return ora(state->reg_h, state);
      
    case 0xb5:
      // ORA L
      return ora(state->reg_l, state);
      
    case 0xb6:
      // ORA M
      return ora(*get_mem_byte(state), state);
      
    case 0xb7:
      // ORA A
      return ora(state->reg_a, state);
      
    case 0xb8:
      // CMP B
      return cmp(state->reg_b, state);
      
    case 0xb9:
      // CMP C
      return cmp(state->reg_c, state);
      
    case 0xba:
      // CMP D
      return cmp(state->reg_d, state);
      
    case 0xbb:
      // CMP E
      return cmp(state->reg_e, state);
      
    case 0xbc:
      // CMP H
      return cmp(state->reg_h, state);
      
    case 0xbd:
      // CMP L
      return cmp(state->reg_l, state);
      
    case 0xbe:
      // CMP M
      return cmp(*get_mem_byte(state), state);
      
    case 0xbf:
      // CMP A
      return cmp(state->reg_a, state);
      
    case 0xc0:
      // RNZ
      return rnz(state);
      
    case 0xc1:
      // POP B
      return pop(&state->reg_b, &state->reg_c, state);
      
    case 0xc2:
      // JNZ
      return jnz(state);
      
    case 0xc3:
      // JMP
      return jmp(state);
      
    case 0xc4:
      // CNZ
      return cnz(state);
      
    case 0xc5:
      // PUSH B
      return push(state->reg_b, state->reg_c, state);
      
    case 0xc6:
      // ADI
      return adi(state);
      
    case 0xc7:
      // RST 0
      return rst(0, state);
      
    case 0xc8:
      // RZ
      return rz(state);
      
    case 0xc9:
      // RET
      return ret(state);
      
    case 0xca:
      // JZ
      return jz(state);
      
    case 0xcb:
      // NONE
      return unused(state);
      
    case 0xcc:
      // CZ
      return cz(state);
      
    case 0xcd:
      // CALL
      return call(state);
      
    case 0xce:
      // ACI
      return aci(state);
      
    case 0xcf:
      // RST 1
      return rst(1, state);
      
    case 0xd0:
      // RNC
      return rnc(state);
      
    case 0xd1:
      // POP D
      return pop(&state->reg_d, &state->reg_e, state);
      
    case 0xd2:
      // JNC
      return jnc(state);
      
    case 0xd3:
      // OUT
      return out(state);
      
    case 0xd4:
      // CNC
      return cnc(state);
      
    case 0xd5:
      // PUSH D
      return push(state->reg_d, state->reg_e, state);
      
    case 0xd6:
      // SUI
      return sui(state);
      
    case 0xd7:
      // RST 2
      return rst(2, state);
    
    case 0xd8:
      // RC
      return rc(state);
      
    case 0xd9:
      // NONE
      return unused(state);
      
    case 0xda:
      // JC
      return jc(state);
      
    case 0xdb:
      // IN
      return in(state);
      
    case 0xdc:
      // CC
      return cc(state);
      
    case 0xdd:
      // NONE
      return unused(state);
      
    case 0xde:
      // SBI
      return sbi(state);
      
    case 0xdf:
      // RST 3
      return rst(3, state);
      
    case 0xe0:
      // RPO
      return rpo(state);
      
    case 0xe1:
      // POP H
      return pop(&state->reg_h, &state->reg_l, state);
      
    case 0xe2:
      // JPO
      return jpo(state);
      
    case 0xe3:
      // XTHL
      return xthl(state);
      
    case 0xe4:
      // CPO
      return cpo(state);
      
    case 0xe5:
      // PUSH H
      return push(state->reg_h, state->reg_l, state);
      
    case 0xe6:
      // ANI
      return ani(state);
      
    case 0xe7:
      // RST 4
      return rst(4, state);
      
    case 0xe8:
      // RPE
      return rpe(state);
      
    case 0xe9:
      // PCHL
      return pchl(state);
      
    case 0xea:
      // JPE
      return jpe(state);
      
    case 0xeb:
      // XCHG
      return xchg(state);
      
    case 0xec:
      // CPE
      return cpe(state);
      
    case 0xed:
      // NONE
      return unused(state);
      
    case 0xee:
      // XRI
      return xri(state);
      
    case 0xef:
      // RST 5
      return rst(5, state);
    
    case 0xf0:
      // RP
      return rp(state);
      
    case 0xf1:
      // POP PSW
      return pop_psw(state);
      
    case 0xf2:
      // JP
      return jp(state);
      
    case 0xf3:
      // DI
      return di(state);
      
    case 0xf4:
      // CP
      return cp(state);
      
    case 0xf5:
      // PUSH PSW
      return push_psw(state);
      
    case 0xf6:
      // ORI
      return ori(state);
      
    case 0xf7:
      // RST 6
      return rst(6, state);
      
    case 0xf8:
      // RM
      return rm(state);
      
    case 0xf9:
      // SPHL
      return sphl(state);
      
    case 0xfa:
      // JM
      return jm(state);
      
    case 0xfb:
      // EI
      return ei(state);
    
    case 0xfc:
      // CM
      return cm(state);
      
    case 0xfd:
      // NONE
      return unused(state);
      
    case 0xfe:
      // CPI
      return cpi(state);
      
    case 0xff:
      // RST 7
      return rst(7, state);
  }
}

int update_state(State8080 *state) {
  if (state->is_interrupted) {

#ifdef LOG_CPU
    OpCode interrupt_op_code = OP_CODES[state->interrupt_instr];
    printf("INTERRUPT -> %-9s", interrupt_op_code.name);
    print_registers_compact(state);
    printf("\n");
#endif

    // Reset the interrupted and interrupt enabled flags
    state->is_interrupted = 0;
    state->inte = 0;
    // back-up the program counter by one since the interrupt "injects" an 
    // additional instruction into the execution
    state->pc--; 
    // Execute the interrupt instruction
    return execute_instr(state->interrupt_instr, state);
  } else {

#ifdef LOG_CPU
    OpCode op_code = OP_CODES[state->mem[state->pc]];
    printf("%4x: ", state->pc);
    switch (op_code.size) {
      case 1:
        printf("%-9s          ", op_code.name);
        break;
      case 2:
        printf("%-9s 0x%2x     ", op_code.name, state->mem[state->pc+1]);
        break;
      case 3:
        printf("%-9s 0x%2x,0x%2x", op_code.name, state->mem[state->pc+2], state->mem[state->pc+1]);
        break;
    }
    printf("   ");
    print_registers_compact(state);
    printf("\n");
#endif

    return execute_instr(state->mem[state->pc], state);
  }
}

unsigned char init_input_func_stub() {
  printf("WARN: Attempt to read data from unmapped input device\n");
  return 0;
}

void init_output_func_stub(unsigned char data) {
  printf("WARN: Attempt to write data to unmapped output device\n");
}

void init_state(State8080 *state) {
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
    // Initialize the input and output handlers with a stub which logs an error message
    state->inputs[i] = init_input_func_stub;
    state->outputs[i] = init_output_func_stub;
  }
}

int read_file_to_mem(const char *filename, const int offset, char *mem, size_t mem_size) {
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

  if (filesize + offset <= mem_size) {
    printf("Loading %ld bytes starting at memory address 0x%x\n", filesize, offset);
  } else {
    printf("Failed to open file - file too large");
    return 0;
  }

  unsigned char *buf = mem + offset;

  fread(buf, filesize, 1, file);
	fclose(file);
  return 1;
}

int load_diagnostic(const char *path, State8080 *state) {
  const int offset = 0x100;
  return read_file_to_mem(path, offset, state->mem, MEM_SIZE_8080);
}

int load_space_invaders(const char *dir, State8080 *state) {
  size_t path_length = (strlen(dir)) + 12; // length of `/invaders.x`
  char part_1[path_length];
  char part_2[path_length];
  char part_3[path_length];
  char part_4[path_length];
  snprintf(part_1, path_length, "%s/invaders.h", dir);
  snprintf(part_2, path_length, "%s/invaders.g", dir);
  snprintf(part_3, path_length, "%s/invaders.f", dir);
  snprintf(part_4, path_length, "%s/invaders.e", dir);
  if (!read_file_to_mem(part_1, 0x0000, state->mem, MEM_SIZE_8080)) return 0;
  if (!read_file_to_mem(part_2, 0x0800, state->mem, MEM_SIZE_8080)) return 0;
  if (!read_file_to_mem(part_3, 0x1000, state->mem, MEM_SIZE_8080)) return 0;
  if (!read_file_to_mem(part_4, 0x1800, state->mem, MEM_SIZE_8080)) return 0;
  return 1;
}

void generate_pixels(unsigned char *pixels, unsigned char *video_memory) {
  for (int i = 0; i < DISPLAY_HEIGHT; i++) {
    for (int j = 0; j < DISPLAY_WIDTH; j++) {
      unsigned short p_mem = (i * DISPLAY_WIDTH) + j; // pixel number in memory
      unsigned char on = (video_memory[(p_mem / 8)] >> (p_mem % 8)) & 1 ? 0xff : 0;
      unsigned int x = i;
      unsigned int y = DISPLAY_WIDTH - j - 1;
      unsigned int p_rot = (y * DISPLAY_HEIGHT) + x; // pixel number on rotated screen
      unsigned int k = p_rot << 2;
      pixels[k] = on;
      pixels[k+1] = on;
      pixels[k+2] = on;
      pixels[k+3] = SDL_ALPHA_OPAQUE;
    }
  }   
}

int main(int argc, char const *argv[]) {
  State8080 state;
  init_state(&state);
  register_io_devices(&state);

  if (argc == 2) {
#ifdef DIAGNOSTIC
    int success = load_diagnostic(argv[1], &state);
#else
    int success = load_space_invaders(argv[1], &state);
#endif
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

  // Initialize SDL components
  SDL_Window *window = SDL_CreateWindow(
    "Emulator Window",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    DISPLAY_HEIGHT,
    DISPLAY_WIDTH,
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
    DISPLAY_HEIGHT, 
    DISPLAY_WIDTH
  );

  unsigned char pixels[PIXEL_BYTES];
  memset(pixels, 0, PIXEL_BYTES);

  SDL_Event e;

  // Screen refresh is 60 hz, 
  // but there's an interrupt twice per refresh
  Uint32 screen_refresh_timeout = SDL_GetTicks() + (1000 / 120);
  int screen_refresh_halfway = 0;

  // Track the number of CPU cycles passed
  int cycles = 0;
  const int CYCLES_PER_FRAME = 16666; // 2 Mhz CPU clock speed over 120hz screen refresh rate = 16666

  // Program Loop
  while (1) {
    // Update the CPU state and add to count of CPU cycles passed
    if (cycles < CYCLES_PER_FRAME) { 
      cycles += update_state(&state);
    
    // Update the Screen once all the CPU cycles have completed AND the 120hz time period has elapsed
    } else if (cycles >= CYCLES_PER_FRAME && SDL_TICKS_PASSED(SDL_GetTicks(), screen_refresh_timeout)) {
      // RST 1 when "halfway", RST 2 at "end of screen"
      unsigned char interrupt_instr = screen_refresh_halfway ? 0xcf : 0xd7;

#ifndef DIAGNOSTIC
      interrupt(interrupt_instr, &state);
#endif

      // Flip the halfway bit, reset the screen timer and cycles count
      screen_refresh_halfway = ~screen_refresh_halfway;
      screen_refresh_timeout = SDL_GetTicks() + (1000 / 120);
      cycles = 0;

      // Prepare the renderer
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      // Transform the pixel data from emulated memory to the texture pixels
      generate_pixels(&pixels[0], &state.mem[0x2400]);
      SDL_UpdateTexture(
        texture,
        NULL,
        &pixels[0],
        DISPLAY_HEIGHT * 4
      );

      // Display the texture on the screen
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
