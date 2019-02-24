#include <stdio.h>
#include <stdlib.h>

const int MAX_BYTE_COUNT = 3;

void printBytes(unsigned char *opPtr, int byteCount) {
  for (int i = 0; i < byteCount; i++) {
    printf("%02x ", opPtr[i]);
  }

  for (int i = byteCount; i <= MAX_BYTE_COUNT; i++) {
    printf("   ");
  }
}

int printOp(unsigned char *opPtr, int pc) {

  printf("%4x:   ", pc);

  int byteCount;

  switch (*opPtr) {
    case 0x00:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("NOP");
    break;

    case 0x01:
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("LXI B 0x%x,0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x02:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("STAX B");
    break;

    case 0x03:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INX B");
    break;

    case 0x04:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR B");
    break;

    case 0x05:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR B");
    break;

    case 0x06:
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI B,0x%x", opPtr[1]);
    break;

    case 0x07:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RLC");
    break;

    // 0x08 No instruction

    case 0x09:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DAD B");
    break;

    case 0x0a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("LDAX B");
    break;

    case 0x0b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCX B");
    break;

    case 0x0c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR C");
    break;

    case 0x0d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR C");
    break;

    case 0x0e:
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI C,0x%x", opPtr[1]);
    break;

    case 0x0f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RRC");
    break;

    // 0x10 No instruction

    case 0x11:
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("LXI D 0x%x,0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x12:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("STAX D");
    break;

    case 0x13:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INX D");
    break;

    case 0x14:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR D");
    break;

    case 0x15:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR D");
    break;

    case 0x16:
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI E,0x%x", opPtr[1]);
    break;

    case 0x17:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RAL");
    break;

    // 0X18

    case 0x19:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DAD D");
    break;

    case 0x1a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("LDAX D");
    break;

    case 0x1b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCX D");
    break;

    case 0x1c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR E");
    break;

    case 0x1d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR E");
    break;

    case 0x1e:
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI E,0x%x", opPtr[1]);
    break;

    case 0x1f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RAR");
    break;

    // 0x20

    case 0x21:
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("LXI 0x%x,0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x22:
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("SHLD 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x23:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INX H");
    break;

    case 0x24:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR H");
    break;

    case 0x25:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR H");
    break;

    case 0x26:
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI H,0x%x", opPtr[1]);
    break;

    case 0x27: // Decimal adjust A (Special)
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DAA");
    break;

    // 0x28

    case 0x29: // Add H&L to H&L
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DAD H");
    break;

    case 0x2a:
    byteCount = 3; // Load H & L direct
    printBytes(opPtr, byteCount);
    printf("LHLD 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x2b: // Decrement H & L
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCX H");
    break;

    case 0x2c: // Increment register
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR L");
    break;

    case 0x2d: // Decrement register
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR L");
    break;

    case 0x2e: // Move immediate register
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI L,0x%x", opPtr[1]);
    break;

    case 0x2f: // Complement A (Special)
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMA");
    break;

    // 0x30

    case 0x31: // Load immediate stack pointer
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("LXI S 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x32: // Store A direct
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("STA  0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x33: // Increment stack pointer
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INX SP");
    break;

    case 0x34: // Incremenet memory
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR M");
    break;

    case 0x35: // Decrement memory
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR M");
    break;

    case 0x36: // Move immediate memory
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI M,0x%x", opPtr[1]);
    break;

    case 0x37: // Set carry (special)
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("STC");
    break;

    // 0x38

    case 0x39: // Add stack pointer to H & L
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DAD SP");
    break;

    case 0x3a:
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("LDA 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0x3b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCX SP");
    break;

    case 0x3c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("INR A");
    break;

    case 0x3d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DCR A");
    break;

    case 0x3e:
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("MVI A,0x%x", opPtr[1]);
    break;

    case 0x3f: // Complement carry (special)
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMC");
    break;

    case 0x40:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,B");
    break;

    case 0x41:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,C");
    break;

    case 0x42:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,D");
    break;

    case 0x43:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,E");
    break;

    case 0x44:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,H");
    break;

    case 0x45:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,L");
    break;

    case 0x46:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,M");
    break;

    case 0x47:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV B,A");
    break;

    case 0x48:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,B");
    break;

    case 0x49:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,C");
    break;

    case 0x4a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,D");
    break;

    case 0x4b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,E");
    break;

    case 0x4c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,H");
    break;

    case 0x4d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,L");
    break;

    case 0x4e:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,M");
    break;

    case 0x4f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV C,A");
    break;

    case 0x50:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,B");
    break;

    case 0x51:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,C");
    break;

    case 0x52:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,D");
    break;

    case 0x53:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,E");
    break;

    case 0x54:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,H");
    break;

    case 0x55:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,L");
    break;

    case 0x56:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,M");
    break;

    case 0x57:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV D,A");
    break;

    case 0x58:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,B");
    break;

    case 0x59:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,C");
    break;

    case 0x5a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,D");
    break;

    case 0x5b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,E");
    break;

    case 0x5c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,H");
    break;

    case 0x5d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,L");
    break;

    case 0x5e:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,M");
    break;

    case 0x5f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV E,A");
    break;

    case 0x60:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,B");
    break;

    case 0x61:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,C");
    break;

    case 0x62:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,D");
    break;

    case 0x63:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,E");
    break;

    case 0x64:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,H");
    break;

    case 0x65:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,L");
    break;

    case 0x66:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,M");
    break;

    case 0x67:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV H,A");
    break;

    case 0x68:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,B");
    break;

    case 0x69:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,C");
    break;

    case 0x6a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,D");
    break;

    case 0x6b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,E");
    break;

    case 0x6c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,H");
    break;

    case 0x6d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,L");
    break;

    case 0x6e:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,M");
    break;

    case 0x6f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV L,A");
    break;

    case 0x70:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,B");
    break;

    case 0x71:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,C");
    break;

    case 0x72:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,D");
    break;

    case 0x73:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,E");
    break;

    case 0x74:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,H");
    break;

    case 0x75:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,L");
    break;

    case 0x76: // Halt (special)
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("HLT");
    break;

    case 0x77:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV M,A");
    break;

    case 0x78:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,B");
    break;

    case 0x79:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,C");
    break;

    case 0x7a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,D");
    break;

    case 0x7b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,E");
    break;

    case 0x7c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,H");
    break;

    case 0x7d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,L");
    break;

    case 0x7e:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,M");
    break;

    case 0x7f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("MOV A,A");
    break;

    case 0x80:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD B");
    break;

    case 0x81:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD C");
    break;

    case 0x82:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD D");
    break;

    case 0x83:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD E");
    break;

    case 0x84:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD H");
    break;

    case 0x85:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD L");
    break;

    case 0x86:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD M");
    break;

    case 0x87:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADD A");
    break;

    case 0x88:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC B");
    break;

    case 0x89:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC C");
    break;

    case 0x8a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC D");
    break;

    case 0x8b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC E");
    break;

    case 0x8c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC H");
    break;

    case 0x8d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC L");
    break;

    case 0x8e:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC M");
    break;

    case 0x8f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ADC A");
    break;

    case 0x90:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB B");
    break;

    case 0x91:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB C");
    break;

    case 0x92:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB D");
    break;

    case 0x93:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB E");
    break;

    case 0x94:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB H");
    break;

    case 0x95:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB L");
    break;

    case 0x96:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB M");
    break;

    case 0x97:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SUB A");
    break;

    case 0x98:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB B");
    break;

    case 0x99:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB C");
    break;

    case 0x9a:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB D");
    break;

    case 0x9b:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB E");
    break;

    case 0x9c:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB H");
    break;

    case 0x9d:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB L");
    break;

    case 0x9e:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB M");
    break;

    case 0x9f:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SBB A");
    break;

    case 0xa0:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA B");
    break;

    case 0xa1:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA C");
    break;

    case 0xa2:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA D");
    break;

    case 0xa3:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA E");
    break;

    case 0xa4:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA H");
    break;

    case 0xa5:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA L");
    break;

    case 0xa6:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA M");
    break;

    case 0xa7:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ANA A");
    break;

    case 0xa8:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA B");
    break;

    case 0xa9:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA C");
    break;

    case 0xaa:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA D");
    break;

    case 0xab:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA E");
    break;

    case 0xac:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA H");
    break;

    case 0xad:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA L");
    break;

    case 0xae:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA M");
    break;

    case 0xaf:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XRA A");
    break;

    case 0xb0:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA B");
    break;

    case 0xb1:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA C");
    break;

    case 0xb2:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA D");
    break;

    case 0xb3:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA E");
    break;

    case 0xb4:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA H");
    break;

    case 0xb5:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA L");
    break;

    case 0xb6:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA M");
    break;

    case 0xb7:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("ORA A");
    break;

    case 0xb8:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP B");
    break;

    case 0xb9:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP C");
    break;

    case 0xba:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP D");
    break;

    case 0xbb:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP E");
    break;

    case 0xbc:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP H");
    break;

    case 0xbd:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP L");
    break;

    case 0xbe:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP M");
    break;

    case 0xbf:
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("CMP A");
    break;

    case 0xc0: // Return on no zero
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RNZ");
    break;

    case 0xc1: // Pop register B & C off stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("POP B");
    break;

    case 0xc2:  // Jump on no zero
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JNZ 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xc3: // Jump unconditional
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JMP 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xc4: // Call on no zero
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CNZ 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xc5: // Push register pair B & C on stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("PUSH B");
    break;

    case 0xc6: // Add immediate to A
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("ADI 0x%x", opPtr[1]);
    break;

    case 0xc7: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 0");
    break;

    case 0xc8: // Return on zero
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RZ");
    break;

    case 0xc9: // Return
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RET");
    break;

    case 0xca: // Jump on zero
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JZ 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    // 0xcb

    case 0xcc: // Call on zero
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CZ 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xcd: // Call unconditionally
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CALL 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xce: // Add immediate to A with carry
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("ACI 0x%x", opPtr[1]);
    break;

    case 0xcf: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 1");
    break;

    case 0xd0: // Return on no carry
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RNC");
    break;

    case 0xd1: // Pop register pair D & E off stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("POP D");
    break;

    case 0xd2: // Jump on no carry
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JNC 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xd3: // Output
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("OUT 0x%x", opPtr[1]);
    break;

    case 0xd4: // Call on no carry
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CNC 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xd5: // Push register pair D & E on stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("PUSH D");
    break;

    case 0xd6: // Subtract immediate from A
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("SUI 0x%x", opPtr[1]);
    break;

    case 0xd7: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 2");
    break;

    case 0xd8: // Return on carry
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RC");
    break;

    // 0xd9

    case 0xda: // Jump on carry
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JC 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xdb: // Input
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("IN 0x%x", opPtr[1]);
    break;

    case 0xdc: // Call on carry
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CC 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    // 0xdd

    case 0xde: // Subtract immediate from A with borrow
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("SBI 0x%x", opPtr[1]);
    break;

    case 0xdf: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 3");
    break;

    case 0xe0: // Return on parity odd
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RPO");
    break;

    case 0xe1: // Pop register pair H & L off stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("POP H");
    break;

    case 0xe2: // Jump on parity odd
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JPO 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xe3: // Exchange top of stack, H & L
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XTHL");
    break;

    case 0xe4: // Call on parity odd
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CPO 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xe5: // Push register pair H & L onto stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("PUSH H");
    break;

    case 0xe6: // And immediate with A
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("ANI 0x%x", opPtr[1]);
    break;

    case 0xe7: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 4");
    break;

    case 0xe8: // Return on parity even
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RPE");
    break;

    case 0xe9: // H & L to program counter
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("PCHL");
    break;

    case 0xea: // Jump on parity even
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JPE 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xeb: // Exchange D & E, H & L registers
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("XCHG");
    break;

    case 0xec: // Call on parity even
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CPE 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    // 0xed

    case 0xee: // Exclusive or immediate with A
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("XRI 0x%x", opPtr[1]);
    break;

    case 0xef: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 5");
    break;

    case 0xf0: // Return on positive
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RP");
    break;

    case 0xf1: // Pop A and Flags off stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("POP PSW");
    break;

    case 0xf2: // Jump on positive
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JP 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xf3: // Disable interrupt
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("DI");
    break;

    case 0xf4: // Call on positive
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CP 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xf5: // Push A and Flags on stack
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("PUSH PSW");
    break;

    case 0xf6: // Or immediate with A
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("ORI 0x%x", opPtr[1]);
    break;

    case 0xf7: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 6");
    break;

    case 0xf8: // Return on minus
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RM");
    break;

    case 0xf9: // H & L to stack pointer
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("SPHL");
    break;

    case 0xfa: // Jump on minus
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("JM 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    case 0xfb: // Enable interrupts
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("EI");
    break;

    case 0xfc: // Call on minus
    byteCount = 3;
    printBytes(opPtr, byteCount);
    printf("CM 0x%x 0x%x", opPtr[2], opPtr[1]);
    break;

    // 0xfd

    case 0xfe: // Compare immediate with A
    byteCount = 2;
    printBytes(opPtr, byteCount);
    printf("CPI 0x%x", opPtr[1]);
    break;

    case 0xff: // Restart
    byteCount = 1;
    printBytes(opPtr, byteCount);
    printf("RST 7");
    break;

    default:
      byteCount = 1;
      printBytes(opPtr, byteCount);
      printf("UNKNOWN");
  }

  printf("\n");

  return byteCount;
}

void read_file(char *filename) {
  FILE *file;
  unsigned long filesize;
  char *buf;
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

  buf = (char *)malloc(filesize + 1);

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

void main(int argc, char *argv[]) {

  if (argc == 2) {
    read_file(argv[1]);
  } else {
    printf("Invalid argument count\n");
  }
}
