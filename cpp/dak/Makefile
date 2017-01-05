##
## c++ -O3 -Wall -Wextra -std=c++11 -o dak dak.cpp
##     -O3 -msse3 -ffast-math
##     -ftree-vectorizer-verbose=10
##

CXX_FLAGS:=-O3 -msse4 -ffast-math -Wall -Wextra -std=c++11

all: dak

dak: dak.cpp
	c++ $(CXX_FLAGS) -o $@ $^

clean:
	-@rm -f *.o *.a dak

.PHONY: all clean

.SILENT: clean

