#include "state.h"

unsigned short bit_shift_register;
unsigned char bit_shift_offset;

void handle_bit_shift_output(unsigned char data) {
    bit_shift_register >>= 8;
    bit_shift_register &= (data << 8);    
}

unsigned char handle_bit_shift_input() {
    return (char) bit_shift_register >> (8 - bit_shift_offset);
}

void handle_bit_shift_offset_output(unsigned char data) {
    bit_shift_offset = data;
}

void register_io_devices(ProcState *state) {
    // Register the space invaders bit shift hardware handlers
    state->outputs[2] = handle_bit_shift_offset_output;
    state->outputs[4] = handle_bit_shift_output;
    state->inputs[3] = handle_bit_shift_input;
}

