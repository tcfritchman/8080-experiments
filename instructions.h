#include "state.h"

/*
 * CARRY BIT INSTRUCTIONS
 */

void cmc(ProcState *state);

void stc(ProcState *state);

/*
 * SINGLE REGISTER INSTRUCTIONS
 */

void inr(unsigned char *data);

void dcr(unsigned char *data);

void cma(ProcState *state);

void daa(ProcState *state);

/*
 * DATA TRANSFER INSTRUCTIONS
 */

void mov(unsigned char data_src, unsigned char *mem_addr_dst);

void stax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void ldax(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

/*
 * REGISTER OR MEMORY TO ACCUMULATOR INSTRUCTIONS
 */

/* 
 * ADD - Add contents of mem_addr to accumulator 
 * Description: The specified byte is added to the contents of the accumulator using two's complement arithmetic
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void add(unsigned char mem_addr, ProcState *state);

/* 
 * ADC - Add contents of mem_addr to accumulator with carry
 * Description: The specified byte plus the content of the Carry bit is added to the contents of the accumulator
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void adc(unsigned char mem_addr, ProcState *state);

/* 
 * SUB - Subtract contents of mem_addr from accumulator
 * Description: The specified byte is subtracted from the
 * accumulator using two's complement arithmetic.
 * If there is no carry out of the high-order bit position,
 * indicating that a borrow occurred, the Carry bit is set;
 * otherwise it is reset. (Note that this differs from an add operation, which resets the carry if no overflow occurs).
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void sub(unsigned char mem_addr, ProcState *state);

/* 
 * SBB - Subtract contents of mem_addr from accumulator with borrow
 * Description: The Carry bit is internally added to the
 * contents of the specified byte. This value is then subtracted
 * from the accumulator using two's complement arithmetic.
 * This instruction is most useful when performing subtractions. It adjusts the result of subtracting two bytes when
 * a previous subtraction has produced a negative result (a borrow).
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void sbb(unsigned char mem_addr, ProcState *state);

/* 
 * ANA - Logical AND contents of mem_addr with accumulator
 * Description: The specified byte is logically ANDed bit
 * by bit with the contents of the accumulator. The Carry bit
 * is reset to zero.
 * The logical AND function of two bits is 1 if and only
 * if both the bits equal 1.
 * Condition bits affected: Carry, Zero, Sign, Parity
 */
void ana(unsigned char mem_addr, ProcState *state);

/* 
 * XRA - Logical Exclusive-Or Register or Memory 
 * With Accumulator (Zero Accumulator)
 * Description: The specified byte is EXCLUSIVE-ORed
 * bit by bit with the contents of the accumulator. The Carry
 * bit is reset to zero
 * Condition bits affected: Carry, Zero, Sign, Parity,
 * Auxiliary Carry
 */
void xra(unsigned char mem_addr, ProcState *state);

/* 
 * ORA - Logical or Register or Memory With Accumulator
 * Description: The specified byte is logically ORed bit
 * by bit with the contents of the accumulator. The carry bit
 * is reset to zero.
 * Condition bits affected: Carry, Zero, Sign, Parity
 */
void ora(unsigned char mem_addr, ProcState *state);

/*
 * CMP - Compare Register or Memory With Accumulator
 * Description: The specified byte is compared to the
 * contents of the accumulator. The comparison is performed
 * by internally subtracting the contents of REG from the accumulator 
 * (leaving both unchanged) and setting the condition bits according 
 * to the result. In particular, the Zero bit is
 * set if the quantities are equal, and reset if they are unequal.
 * Since a subtract operation is performed, the Carry bit will be
 * set if there is no carry out of bit 7, indicati ng that the
 * contents of REG are greater than the contents of the accumulator, and reset otherwise.
 * NOTE: If the two quantities to be compared differ in sign,
 * the sense of the Carry bit is reversed.
 * Condition bits affected: Carry, Zero, Sign, Parity,
 * Auxiliary Carry
 */
void cmp(unsigned char mem_addr, ProcState *state);

/*
 * ROTATE ACCUMULATOR INSTRUCTIONS
 */

/*
 * RLC - Rotate Accumulator Left
 * Description: The Carry bit is set equal to the highorder bit of the accumulator. 
 * The contents of the accumulator are rotated one bit position to the left, with the 
 * highorder bit being transferred to the low-order bit position of the accumulator.
 * Condition bits affected: Carry
 */
void rlc(ProcState *state);

/*
 * RRC - Rotate Accumulator Right
 * Description: The carry bit is set equal to the low-order
 * bit of the accumulator. The contents of the accumulator are
 * rotated one bit position to the right, with the low-order bit
 * being transferred to the high-order bit position of the
 * accumulator.
 * Condition bits affected: Carry
 */
void rrc(ProcState *state);

/*
 * RAL - Rotate Accumulator Left Through Carry
 * Description: The contents of the accumulator are rotated one bit position to the left.
 * The high-order bit of the accumulator replaces the
 * Carry bit, while the Carry bit replaces the high-order bit of
 * the accumulator.
 * Condition bits affected: Carry
 */
void ral(ProcState *state);

/*
 * RAR - Rotate Accumulator Right Through Carry
 * Description: The contents of the accumulator are rotated one bit position to the right.
 * The low-order bit of the accumulator replaces the
 * carry bit, while the carry bit replaces the high-order bit of
 * the accumulator.
 * Condition bits affected: Carry
 */
void rar(ProcState *state);

/*
 * REGISTER PAIR INSTRUCTIONS
 */

/*
 * PUSH - Push Data Onto Stack
 * Description: The contents of the specified register pair
 * are saved in two bytes of memory indicated by the stack
 * pointer SP.
 * Condition bits affected: None
 */
void push(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

/*
 * PUSH PSW - Push specifically PSW Onto Stack
 * Condition bits affected: None
 */
void push_psw(ProcState *state);

void pop(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo, ProcState *state);

void pop_psw(ProcState *state);

void dad(unsigned char data_hi, unsigned char data_lo, ProcState *state);

void inx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo);

void dcx(unsigned char *mem_addr_hi, unsigned char *mem_addr_lo);

void xchg(ProcState *state);

void xthl(ProcState *state);

void sphl(ProcState *state);

/*
 * IMMEDIATE INSTRUCTIONS
 */

// TODO: Note - I believe these instructions share the same functionality
// as the REGISTER OR MEMORY TO ACCUMULATOR instructions.

/*
 * DIRECT ADDRESSING INSTRUCTIONS
 */

void sta(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void lda(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void shld(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void lhld(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

/*
 * JUMP INSTRUCTIONS
 */

void pchl(ProcState *state);

void jmp(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jnc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jnz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jm(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jp(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jpe(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void jpo(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

/*
 * CALL SUBROUTINE INSTRUCTIONS
 */

void call(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cnc(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cnz(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cm(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cp(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cpe(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

void cpo(unsigned char mem_addr_hi, unsigned char mem_addr_lo, ProcState *state);

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

// TODO

/*
 * HALT INSTRUCTION
 */

// TODO