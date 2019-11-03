#include "state.h"

/*
 * NOP AND UNUSED INSTRUCTIONS
 */

int nop(State8080 *state);

int unused(State8080 *state);

/*
 * CARRY BIT INSTRUCTIONS
 */

int cmc(State8080 *state);

int stc(State8080 *state);

/*
 * SINGLE REGISTER INSTRUCTIONS
 */

int inr(unsigned char *data, State8080 *state);

int dcr(unsigned char *data, State8080 *state);

int cma(State8080 *state);

int daa(State8080 *state);

/*
 * DATA TRANSFER INSTRUCTIONS
 */

int mov(unsigned char data_src, unsigned char *mem_addr_dst, State8080 *state);

int stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, State8080 *state);

int ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, State8080 *state);

/*
 * REGISTER OR MEMORY TO ACCUMULATOR INSTRUCTIONS
 */

int add(unsigned char mem_addr, State8080 *state);

int adc(unsigned char mem_addr, State8080 *state);

int sub(unsigned char mem_addr, State8080 *state);

int sbb(unsigned char mem_addr, State8080 *state);

int ana(unsigned char mem_addr, State8080 *state);

int xra(unsigned char mem_addr, State8080 *state);

int ora(unsigned char mem_addr, State8080 *state);

int cmp(unsigned char mem_addr, State8080 *state);

/*
 * ROTATE ACCUMULATOR INSTRUCTIONS
 */

int rlc(State8080 *state);

int rrc(State8080 *state);

int ral(State8080 *state);

int rar(State8080 *state);

/*
 * REGISTER PAIR INSTRUCTIONS
 */

int push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, State8080 *state);

int push_psw(State8080 *state);

int pop(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, State8080 *state);

int pop_psw(State8080 *state);

int dad(unsigned char data_hi, unsigned char data_lo, State8080 *state);

int dad_16(unsigned short *data, State8080 *state);

int inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, State8080 *state);

int inx_16(unsigned short *data, State8080 *state);

int dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, State8080 *state);

int dcx_16(unsigned short *data, State8080 *state);

int xchg(State8080 *state);

int xthl(State8080 *state);

int sphl(State8080 *state);

/*
 * IMMEDIATE INSTRUCTIONS
 */

int lxi(unsigned char *dest_hi, unsigned char *dest_lo, State8080 *state);

int lxi_16(unsigned short *dest, State8080 *state);

int mvi(unsigned char *dest, State8080 *state);

int mvi_m(unsigned char *dest, State8080 *state);

int adi(State8080 *state);

int aci(State8080 *state);

int sui(State8080 *state);

int sbi(State8080 *state);

int ani(State8080 *state);

int xri(State8080 *state);

int ori(State8080 *state);

int cpi(State8080 *state);

/*
 * DIRECT ADDRESSING INSTRUCTIONS
 */

int sta(State8080 *state);

int lda(State8080 *state);

int shld(State8080 *state);

int lhld(State8080 *state);

/*
 * JUMP INSTRUCTIONS
 */

int pchl(State8080 *state);

int jmp(State8080 *state);

int jc(State8080 *state);

int jnc(State8080 *state);

int jz(State8080 *state);

int jnz(State8080 *state);

int jm(State8080 *state);

int jp(State8080 *state);

int jpe(State8080 *state);

int jpo(State8080 *state);

/*
 * CALL SUBROUTINE INSTRUCTIONS
 */

int call(State8080 *state);

int cc(State8080 *state);

int cnc(State8080 *state);

int cz(State8080 *state);

int cnz(State8080 *state);

int cm(State8080 *state);

int cp(State8080 *state);

int cpe(State8080 *state);

int cpo(State8080 *state);

/*
 * RETURN FROM SUBROUTINE INSTRUCTIONS
 */

int ret(State8080 *state);

int rc(State8080 *state);

int rnc(State8080 *state);

int rz(State8080 *state);

int rnz(State8080 *state);

int rm(State8080 *state);

int rp(State8080 *state);

int rpe(State8080 *state);

int rpo(State8080 *state);

/*
 * RST INSTRUCTION
 */

int rst(unsigned char exp, State8080 *state);

/*
 * INTERRUPT FLIP-FLOP INSTRUCTIONS
 */

int ei(State8080 *state);

int di(State8080 *state);

/*
 * INPUT/OUTPUT INSTRUCTIONS
 */

int in(State8080 *state);

int out(State8080 *state);

/*
 * HALT INSTRUCTION
 */

int hlt(State8080 *state);
