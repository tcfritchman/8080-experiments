#include <stdio.h>
#include <stdlib.h>
#include "op_codes.h"

const int MAX_BYTE_COUNT = 3;

void printPC(int pc) {
  printf("%4x:   ", pc);
}

void printBytes(unsigned char *opPtr, int byteCount) {
  for (int i = 0; i < byteCount; i++) {
    printf("%02x ", opPtr[i]);
  }

  for (int i = byteCount; i <= MAX_BYTE_COUNT; i++) {
    printf("   ");
  }
}

void printInstr(unsigned char *opPtr, OpCode op) {
  switch (op.size) {
    case 1:
      printf("%s", op.name);
      break;
    case 2:
      printf("%s,0x%x", op.name, opPtr[1]);
      break;
    case 3:
      printf("%s 0x%x,0x%x", op.name, opPtr[2], opPtr[1]);
      break;
  }
}

int printOp(unsigned char *opPtr, int pc) {
  OpCode op = OP_CODES[*opPtr];
  printPC(pc);
  printBytes(opPtr, op.size);
  printInstr(opPtr, op);
  printf("\n");
  return op.size;
}

void read_file(char *filename) {
  FILE *file;
  unsigned long filesize;
  unsigned char *buf;
  int pc = 0;

  file = fopen(filename, "rb");

  if (file == NULL) {
    printf("Failed to open file\n");
    return;
  }

  fseek(file, 0, SEEK_END);
	filesize=ftell(file);
	fseek(file, 0, SEEK_SET);

  printf("- Dissassembling %ld bytes -\n\n", filesize);

  buf = (unsigned char *)malloc(filesize + 1);

  if (!buf) {
    printf("Failed to allocate memory\n");
    fclose(file);
    return;
  }

  fread(buf, filesize, 1, file);
	fclose(file);

  while (pc < filesize) {
    pc += printOp(&buf[pc], pc);
  }

  free(buf);
}

int main(int argc, char *argv[]) {

  if (argc == 2) {
    read_file(argv[1]);
    return 0;
  } else {
    printf("Invalid argument count\n");
    return 1;
  }
}
