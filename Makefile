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
CFLAGS  =  
LDFLAGS = -lchicken

SS   := $(wildcard *.ss)
CSS  := $(patsubst %.ss,%.c,$(SS))
OBJS := $(patsubst %.c,%.o,$(CSS))

#
# Targets
#
all: cc-gen-a

cc-gen-a: $(OBJS)
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

$(OBJS): $(CSS)
	$(CC) $(CFLAGS) -c $? -o $@ 

$(CSS): $(SS)
	chicken $? 

.o: .c

clean:
	-@echo cleaning...
	-@rm -f *.c *.o cc-gen-a 2>/dev/null

#
# Explicit recipes
#
.SILENT: clean
.PHONY:  all clean

