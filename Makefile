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
CHICKEN = chicken 
ifeq ($(SYSTEM), Msys)
	CFLAGSI = -IC:/MinGW/local/include/chicken -LC:/MinGW/local/lib
	LDFLAGL = -Xlinker --enable-auto-import
	MODEXT  = .exe
else
	CFLAGSI = 
	LDFLAGL = 
	MODEXT  = 
endif
CFLAGSW = -Wall -Wno-unused-variable 
CFLAGS  = -O3 -fomit-frame-pointer -fno-strict-aliasing $(CFLAGSW) $(CFLAGSI)
LDFLAGS = -lchicken $(LDFLAGL) 
CHFLAGS = -feature srfi-1 

#
# Files
#
SS      := $(wildcard *.ss)
CSS     := $(patsubst %.ss,%.c,$(SS))
OBJS    := $(patsubst %.c,%.o,$(CSS))
MODULES := $(patsubst %.ss,%$(MODEXT),$(SS))

#
# Targets
#
all: modules run

modules: $(MODULES)

$(MODULES): $(OBJS)

%$(MODEXT): %.o
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

%.o: %.c $(CSS)
	$(CC) $(CFLAGS) -c $< -o $@ 

%.c: %.ss $(SS)
	$(CHICKEN) $< $(CHFLAGS) 

run: $(MODULES)
	-@echo Running: $(MODULES) 
	-@$(foreach file,$(MODULES), if [ -x $(file) ]; then echo $(file) | xargs -Ifile sh -c ./file ; fi; )

clean:
	-@echo cleaning...
	-@rm -f *.c *.o *.so *.a *.exe *.dll *.lib 2>/dev/null
	-@rm -f $(MODULES)

#
# Explicit recipes
#
.SILENT: clean

.PHONY:  all modules run clean

.DEFAULT: all

.SECONDARY:

.INTERMEDIATE:


