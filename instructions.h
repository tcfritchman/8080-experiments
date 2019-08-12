#include "state.h"

/*
 * NOP AND UNUSED INSTRUCTIONS
 */

void nop(ProcState *state);

void unused(ProcState *state);

/*
 * CARRY BIT INSTRUCTIONS
 */

void cmc(ProcState *state);

void stc(ProcState *state);

/*
 * SINGLE REGISTER INSTRUCTIONS
 */

void inr(unsigned char *data, ProcState *state);

void dcr(unsigned char *data, ProcState *state);

void cma(ProcState *state);

void daa(ProcState *state);

/*
 * DATA TRANSFER INSTRUCTIONS
 */

void mov(unsigned char data_src, unsigned char *mem_addr_dst, ProcState *state);

void stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

/*
 * REGISTER OR MEMORY TO ACCUMULATOR INSTRUCTIONS
 */

void add(unsigned char mem_addr, ProcState *state);

void adc(unsigned char mem_addr, ProcState *state);

void sub(unsigned char mem_addr, ProcState *state);

void sbb(unsigned char mem_addr, ProcState *state);

void ana(unsigned char mem_addr, ProcState *state);

void xra(unsigned char mem_addr, ProcState *state);

void ora(unsigned char mem_addr, ProcState *state);

void cmp(unsigned char mem_addr, ProcState *state);

/*
 * ROTATE ACCUMULATOR INSTRUCTIONS
 */

void rlc(ProcState *state);

void rrc(ProcState *state);

void ral(ProcState *state);

void rar(ProcState *state);

/*
 * REGISTER PAIR INSTRUCTIONS
 */

void push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void push_psw(ProcState *state);

void pop(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

void pop_psw(ProcState *state);

void dad(unsigned char data_hi, unsigned char data_lo, ProcState *state);

void dad_16(unsigned short *data, ProcState *state);

void inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

void inx_16(unsigned short *data, ProcState *state);

void dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

void dcx_16(unsigned short *data, ProcState *state);

void xchg(ProcState *state);

void xthl(ProcState *state);

void sphl(ProcState *state);

/*
 * IMMEDIATE INSTRUCTIONS
 */

void lxi(unsigned char *dest_hi, unsigned char *dest_lo, ProcState *state);

void lxi_16(unsigned short *dest, ProcState *state);

void mvi(unsigned char *dest, ProcState *state);

void adi(ProcState *state);

void aci(ProcState *state);

void sui(ProcState *state);

void sbi(ProcState *state);

void ani(ProcState *state);

void xri(ProcState *state);

void ori(ProcState *state);

void cpi(ProcState *state);

/*
 * DIRECT ADDRESSING INSTRUCTIONS
 */

void sta(ProcState *state);

void lda(ProcState *state);

void shld(ProcState *state);

void lhld(ProcState *state);

/*
 * JUMP INSTRUCTIONS
 */

void pchl(ProcState *state);

void jmp(ProcState *state);

void jc(ProcState *state);

void jnc(ProcState *state);

void jz(ProcState *state);

void jnz(ProcState *state);

void jm(ProcState *state);

void jp(ProcState *state);

void jpe(ProcState *state);

void jpo(ProcState *state);

/*
 * CALL SUBROUTINE INSTRUCTIONS
 */

void call(ProcState *state);

void cc(ProcState *state);

void cnc(ProcState *state);

void cz(ProcState *state);

void cnz(ProcState *state);

void cm(ProcState *state);

void cp(ProcState *state);

void cpe(ProcState *state);

void cpo(ProcState *state);

/*
 * RETURN FROM SUBROUTINE INSTRUCTIONS
 */

void ret(ProcState *state);

void rc(ProcState *state);

void rnc(ProcState *state);

void rz(ProcState *state);

void rnz(ProcState *state);

void rm(ProcState *state);

void rp(ProcState *state);

void rpe(ProcState *state);

void rpo(ProcState *state);

/*
 * RST INSTRUCTION
 */

void rst(unsigned char exp, ProcState *state);

/*
 * INTERRUPT FLIP-FLOP INSTRUCTIONS
 */

void ei(ProcState *state);

void di(ProcState *state);

/*
 * INPUT/OUTPUT INSTRUCTIONS
 */

void in(ProcState *state);

void out(ProcState *state);

/*
 * HALT INSTRUCTION
 */

void hlt(ProcState *state);