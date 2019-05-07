#ifndef _STRUCT_OP_CODE_
#define _STRUCT_OP_CODE_

struct OpCode;

typedef struct OpCode {
  const unsigned char code;
  const char *name;
  const unsigned char size;
} OpCode;

extern const OpCode OP_CODES[];

#endif
