#include "state.h"

/* 
 * ADD - Add contents of mem_addr to accumulator 
 * Description: The specified byte is added to the contents of the accumulator using two's complement arithmetic
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void addx(unsigned char *mem_addr, ProcState *state);

/* 
 * ADC - Add contents of mem_addr to accumulator with carry
 * Description: The specified byte plus the content of the Carry bit is added to the contents of the accumulator
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void adcx(unsigned char *mem_addr, ProcState *state);

/* 
 * SUB - Subtract contents of mem_addr from accumulator
 * Description: The specified byte is subtracted from the
 * accumulator using two's complement arithmetic.
 * If there is no carry out of the high-order bit position,
 * indicating that a borrow occurred, the Carry bit is set;
 * otherwise it is reset. (Note that this differs from an add operation, which resets the carry if no overflow occurs).
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void subx(unsigned char *mem_addr, ProcState *state);

/* 
 * SBB - Subtract contents of mem_addr from accumulator with borrow
 * Description: The Carry bit is internally added to the
 * contents of the specified byte. This value is then subtracted
 * from the accumulator using two's complement arithmetic.
 * This instruction is most useful when performing subtractions. It adjusts the result of subtracting two bytes when
 * a previous subtraction has produced a negative result (a borrow).
 * Condition bits affected: Carry, Sign, Zero, Parity, Auxiliary Carry
 */
void sbbx(unsigned char *mem_addr, ProcState *state);

/* 
 * ANA - Logical AND contents of mem_addr with accumulator
 * Description: The specified byte is logically ANDed bit
 * by bit with the contents of the accumulator. The Carry bit
 * is reset to zero.
 * The logical AND function of two bits is 1 if and only
 * if both the bits equal 1.
 * Condition bits affected: Carry, Zero, Sign, Parity
 */
void anax(unsigned char *mem_addr, ProcState *state);

/* 
 * XRA - Logical Exclusive-Or Register or Memory 
 * With Accumulator (Zero Accumulator)
 * Description: The specified byte is EXCLUSIVE-ORed
 * bit by bit with the contents of the accumulator. The Carry
 * bit is reset to zero
 * Condition bits affected: Carry, Zero, Sign, Parity,
 * Auxiliary Carry
 */
void xrax(unsigned char *mem_addr, ProcState *state);

/* 
 * ORA - Logical or Register or Memory With Accumulator
 * Description: The specified byte is logically ORed bit
 * by bit with the contents of the accumulator. The carry bit
 * is reset to zero.
 * Condition bits affected: Carry, Zero, Sign, Parity
 */
void orax(unsigned char *mem_addr, ProcState *state);
