#ifndef _STRUCT_PROC_STATE_
#define _STRUCT_PROC_STATE_

struct ProcState;

typedef struct ProcState {
  char mem[65536];
  char reg_b;
  char reg_c;
  char reg_d;
  char reg_e;
  char reg_h;
  char reg_l;
  char reg_a;
  int sign;
  int zero;
  int parity;
  int carry;
  int aux_carry;
  unsigned short pc;
  unsigned short sp;
} ProcState;

#endif
