#include "state.h"

/*
 * NOP AND UNUSED INSTRUCTIONS
 */

int nop(ProcState *state);

int unused(ProcState *state);

/*
 * CARRY BIT INSTRUCTIONS
 */

int cmc(ProcState *state);

int stc(ProcState *state);

/*
 * SINGLE REGISTER INSTRUCTIONS
 */

int inr(unsigned char *data, ProcState *state);

int dcr(unsigned char *data, ProcState *state);

int cma(ProcState *state);

int daa(ProcState *state);

/*
 * DATA TRANSFER INSTRUCTIONS
 */

int mov(unsigned char data_src, unsigned char *mem_addr_dst, ProcState *state);

int stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

int ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

/*
 * REGISTER OR MEMORY TO ACCUMULATOR INSTRUCTIONS
 */

int add(unsigned char mem_addr, ProcState *state);

int adc(unsigned char mem_addr, ProcState *state);

int sub(unsigned char mem_addr, ProcState *state);

int sbb(unsigned char mem_addr, ProcState *state);

int ana(unsigned char mem_addr, ProcState *state);

int xra(unsigned char mem_addr, ProcState *state);

int ora(unsigned char mem_addr, ProcState *state);

int cmp(unsigned char mem_addr, ProcState *state);

/*
 * ROTATE ACCUMULATOR INSTRUCTIONS
 */

int rlc(ProcState *state);

int rrc(ProcState *state);

int ral(ProcState *state);

int rar(ProcState *state);

/*
 * REGISTER PAIR INSTRUCTIONS
 */

int push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

int push_psw(ProcState *state);

int pop(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

int pop_psw(ProcState *state);

int dad(unsigned char data_hi, unsigned char data_lo, ProcState *state);

int dad_16(unsigned short *data, ProcState *state);

int inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

int inx_16(unsigned short *data, ProcState *state);

int dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

int dcx_16(unsigned short *data, ProcState *state);

int xchg(ProcState *state);

int xthl(ProcState *state);

int sphl(ProcState *state);

/*
 * IMMEDIATE INSTRUCTIONS
 */

int lxi(unsigned char *dest_hi, unsigned char *dest_lo, ProcState *state);

int lxi_16(unsigned short *dest, ProcState *state);

int mvi(unsigned char *dest, ProcState *state);

int mvi_m(unsigned char *dest, ProcState *state);

int adi(ProcState *state);

int aci(ProcState *state);

int sui(ProcState *state);

int sbi(ProcState *state);

int ani(ProcState *state);

int xri(ProcState *state);

int ori(ProcState *state);

int cpi(ProcState *state);

/*
 * DIRECT ADDRESSING INSTRUCTIONS
 */

int sta(ProcState *state);

int lda(ProcState *state);

int shld(ProcState *state);

int lhld(ProcState *state);

/*
 * JUMP INSTRUCTIONS
 */

int pchl(ProcState *state);

int jmp(ProcState *state);

int jc(ProcState *state);

int jnc(ProcState *state);

int jz(ProcState *state);

int jnz(ProcState *state);

int jm(ProcState *state);

int jp(ProcState *state);

int jpe(ProcState *state);

int jpo(ProcState *state);

/*
 * CALL SUBROUTINE INSTRUCTIONS
 */

int call(ProcState *state);

int cc(ProcState *state);

int cnc(ProcState *state);

int cz(ProcState *state);

int cnz(ProcState *state);

int cm(ProcState *state);

int cp(ProcState *state);

int cpe(ProcState *state);

int cpo(ProcState *state);

/*
 * RETURN FROM SUBROUTINE INSTRUCTIONS
 */

int ret(ProcState *state);

int rc(ProcState *state);

int rnc(ProcState *state);

int rz(ProcState *state);

int rnz(ProcState *state);

int rm(ProcState *state);

int rp(ProcState *state);

int rpe(ProcState *state);

int rpo(ProcState *state);

/*
 * RST INSTRUCTION
 */

int rst(unsigned char exp, ProcState *state);

/*
 * INTERRUPT FLIP-FLOP INSTRUCTIONS
 */

int ei(ProcState *state);

int di(ProcState *state);

/*
 * INPUT/OUTPUT INSTRUCTIONS
 */

int in(ProcState *state);

int out(ProcState *state);

/*
 * HALT INSTRUCTION
 */

int hlt(ProcState *state);
