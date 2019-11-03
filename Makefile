SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

emulator : emulator.o instructions.o invaders_io.o state_util.o op_codes.o util.o
	cc $(SDL_CFLAGS) -o emulator.out emulator.o instructions.o invaders_io.o state_util.o op_codes.o util.o $(SDL_LDFLAGS)

emulator.o : emulator.c
	cc $(SDL_CFLAGS) -c emulator.c $(SDL_LDFLAGS)

instructions.o : instructions.c 
	cc -c instructions.c

invaders_io.o : invaders_io.c
	cc -c invaders_io.c

state_util.o : state_util.c
	cc -c state_util.c

util.o : util.c
	cc -c util.c

op_codes.o : op_codes.c
	cc -c op_codes.c

clean :
	rm -f *.out *.o
