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