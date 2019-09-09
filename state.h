#ifndef _STRUCT_PROC_STATE_
#define _STRUCT_PROC_STATE_

struct ProcState;

typedef struct ProcState {
  unsigned char mem[65536];
  unsigned char reg_b;
  unsigned char reg_c;
  unsigned char reg_d;
  unsigned char reg_e;
  unsigned char reg_h;
  unsigned char reg_l;
  unsigned char reg_a; // "Accumulator"
  int sign;
  int zero;
  int parity;
  int carry;
  int aux_carry;
  unsigned short pc;
  unsigned short sp;
  unsigned char (*inputs[256]) ();
  void (*outputs[256]) (unsigned char data);
  int inte; // Interrupts Enabled
  int is_interrupted; // An interrupt has occurred
  unsigned char interrupt_instr; // The instruction supplied via the interrupt
} ProcState;

#endif
