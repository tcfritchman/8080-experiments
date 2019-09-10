#include <stdio.h>
#include "state.h"

/*
Device information taken from http://computerarcheology.com/Arcade/SpaceInvaders/Hardware.html
*/

unsigned short bit_shift_register;
unsigned char bit_shift_offset;
unsigned char input_port_0; // Not used
unsigned char input_port_1 = 0b00001000;
unsigned char input_port_2 = 0b00000000;

void handle_bit_shift_write(unsigned char data) {
    bit_shift_register >>= 8;
    bit_shift_register &= (data << 8);    
}

unsigned char handle_bit_shift_read() {
    return (char) bit_shift_register >> (8 - bit_shift_offset);
}

void handle_bit_shift_offset_write(unsigned char data) {
    bit_shift_offset = data;
}

void handle_port_3_sounds(unsigned char data) {
    if (1 & data) {
        printf("Playing SX1\n");      
    }
    if (2 & data) {
        printf("Playing SX2\n");
    }
    if (4 & data) {
        printf("Playing SX3\n");       
    }
    if (8 & data) {
        printf("Playing SX4\n");
    }
    if (16 & data) {
        printf("Playing SX5\n");
    }
}

void handle_port_5_sounds(unsigned char data) {
    if (1 & data) {
        printf("Playing SX6\n");      
    }
    if (2 & data) {
        printf("Playing SX7\n");
    }
    if (4 & data) {
        printf("Playing SX8\n");       
    }
    if (8 & data) {
        printf("Playing SX9\n");
    }
    if (16 & data) {
        printf("Playing SX10\n");
    }
}

unsigned char handle_port_1_inputs() {
    return input_port_1;
}

unsigned char handle_port_2_inputs() {
    return input_port_2;
}

void register_io_devices(ProcState *state) {
    // Register the space invaders bit shift hardware handlers
    state->outputs[2] = handle_bit_shift_offset_write;
    state->outputs[4] = handle_bit_shift_write;
    state->inputs[3] = handle_bit_shift_read;
    // Register inputs
    state->inputs[1] = handle_port_1_inputs;
    state->inputs[2] = handle_port_2_inputs;
    // Register sounds
    state->outputs[3] = handle_port_3_sounds;
    state->outputs[5] = handle_port_5_sounds;
}

