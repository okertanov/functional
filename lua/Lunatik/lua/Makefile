## --------------------------------------------------
## Makefile - Lua & C++ module (to build locally)
## okertanov@gmail.com (c) 2010
## --------------------------------------------------

CC=g++

all: MyBot

LOBJS=lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o \
	  llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o \
	  lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o lauxlib.o \
	  lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o \
	  lstrlib.o loadlib.o linit.o MyBot.cc

%.o : %.c
	$(CC) -O3 -funroll-loops -c $<

%.o : %.cpp
	$(CC) -O3 -funroll-loops -c $<

MyBot: $(LOBJS)
	$(CC) -O2 -o MyBot $(LOBJS) -lm

clean:
	-@rm -f ./MyBot ./MyBot.exe ./*.o

