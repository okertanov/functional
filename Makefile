# ###################################################################
# CC-GEN 
# Copyright (c) Oleg Kertanov <okertanov@gmail.com> 2011
#
# Makefile
# ###################################################################

#
# Defines
#
CC      = gcc
CFLAGSW = -Wall -Wno-unused-variable  
CFLAGS  = -O3 -fomit-frame-pointer -fno-strict-aliasing $(CFLAGSW)
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
	-@rm -f *.c *.o cc-gen-a 2>/dev/null

#
# Explicit recipes
#
.SILENT: clean
.PHONY:  all clean

