emulator : emulator.o program_state.o op_codes.o
	cc -o emulator.out emulator.o program_state.o op_codes.o

emulator.o : emulator.c program_state.h op_codes.h
	cc -c emulator.c

clean :
	rm emulator *.o
