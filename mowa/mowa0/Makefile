##    Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
##    All rights reserved.

CC=gcc
CXX=g++
RM=rm -f
MV=mv

MODULE_NAME := mowa0

CXX_CFLAGS  := -Wall -Wextra -Wcast-align -Wundef -std=c++0x \
               -DTARGET_POSIX=1 -march=native -mtune=native  \
               -D_FORTIFY_SOURCE=2 -g -DDEBUG -D_UNICODE

SOURCES :=           \
    Lexer.cpp        \
    Parser.cpp       \
    SyntaxTree.cpp   \
    Environment.cpp  \
    Reader.cpp       \
    Evaluator.cpp    \
    Printer.cpp      \
    Platform.cpp     \
    CommandLine.cpp  \
    mowa0.cpp

OBJECTS := $(patsubst %.cpp,%.obj,$(SOURCES))

all: $(MODULE_NAME)


$(MODULE_NAME): $(OBJECTS)
	$(CXX) $(CXX_CFLAGS) $(CXX_LDFLAGS) $? -o $@

%.obj: %.cpp
	$(CXX) $(CXX_CFLAGS) -c $< -o $@

clean:
	-@$(RM) *.obj *.o *.exe *.lib *.a

.DEFAULT: all

.PHONY: all clean

.SILENT: clean

