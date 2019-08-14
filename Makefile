SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

emulator : emulator.o instructions.o state_util.o op_codes.o
	cc $(SDL_CFLAGS) -o emulator.out emulator.o instructions.o state_util.o op_codes.o $(SDL_LDFLAGS)

emulator.o : emulator.c state_util.h instructions.h state.h
	cc $(SDL_CFLAGS) -c emulator.c $(SDL_LDFLAGS)

instructions.o : instructions.c state_util.h state.h 
	cc -c instructions.c

state_util.o : state_util.c state.h
	cc -c state_util.c

op_codes.o : op_codes.c
	cc -c op_codes.c

clean :
	rm -f *.out *.o
