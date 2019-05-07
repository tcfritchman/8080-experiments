emulator : emulator.o state_util.o op_codes.o
	cc -o emulator.out emulator.o state_util.o op_codes.o

emulator.o : emulator.c state_util.h state.h
	cc -c emulator.c

state_util.o : state_util.c state.h
	cc -c state_util.c

op_codes.o : op_codes.c
	cc -c op_codes.c

clean :
	rm -f *.out *.o
