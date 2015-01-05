
CXXFLAGS=-Ilua/src -std=c++1y -Wall
LDFLAGS=-Llua/src -static -llua -lstdc++

all: liblua.a Lunar.exe

liblua.a: lua
	make -C lua/src generic

%.o: %.cpp
	g++ -c $(CXXFLAGS) $< -o $@
	
Lunar.o: Lunar.h

LunarExports.o: LunarExports.h

Lunar.exe: Main.o Lunar.o LunarExports.o
	g++ $? -o $@ $(LDFLAGS)

clean:
	-@rm -f Lunar Lunar.exe Lunar.o LunarExports.o Main.o
	-@make -C lua/src clean
