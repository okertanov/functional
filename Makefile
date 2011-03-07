# ###################################################################
# CC-GEN 
# Copyright (c) Oleg Kertanov <okertanov@gmail.com> 2011
#
# Makefile
# ###################################################################

#
# Platform
#
SYSTEM ?= $(shell uname -o)

#
# Defines
#
CC      = gcc
ifeq ($(SYSTEM), Msys)
	CFLAGSI = -IC:/MinGW/local/include/chicken -LC:/MinGW/local/lib
else
	CFLAGSI = 
endif
CFLAGSW = -Wall -Wno-unused-variable  
CFLAGS  = -O3 -fomit-frame-pointer -fno-strict-aliasing $(CFLAGSW) $(CFLAGSI)
LDFLAGS = -lchicken 

SS     := $(wildcard *.ss)
CSS    := $(patsubst %.ss,%.c,$(SS))
OBJS   := $(patsubst %.c,%.o,$(CSS))

MODULE  = cc-gen-a

#
# Targets
#
all: $(MODULE)

$(MODULE): $(OBJS)
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

$(OBJS): $(CSS)
	$(CC) $(CFLAGS) -c $? -o $@ 

$(CSS): $(SS)
	chicken $? 

clean:
	-@echo cleaning...
	-@rm -f *.c *.o cc-gen-a cc-gen-a.exe 2>/dev/null

#
# Explicit recipes
#
.SILENT: clean
.PHONY:  all clean

