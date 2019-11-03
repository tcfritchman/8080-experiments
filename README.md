# 8080-experiments #
Emulation of the Intel 8080 CPU as well as hardware for popular video arcade machines which used the 8080.

Much of the system being emulated has been documented at this wonderful site, [Computer Archaeology](http://computerarcheology.com/Arcade/SpaceInvaders/), which provides a very interesting look into the history and implemtation specifics of the machines and the code that runs on them.

Hardware components that have been emulated in this project include:
* The Intel 8080 CPU
* A 256x224 black & white raster display
* Player 1 buttons & controls including coin slot and tilt switch
* Bit shift hardware required by Space Invaders code

Unimplemented:
* Player 2 controls
* Sound

## Compiling and running the code: ##
The emulator has a dependency on [SDL2](https://www.libsdl.org/download-2.0.php) so regardless of which system it's being compiled for, SDL2 must be installed.

### Linux/Debian ###
Install SDL2 libs: 

```sudo apt-get install libsdl2-dev```

Once SDL2 is installed, simply run `make`. To run the project: `./emulator.out name-of-rom-file`
