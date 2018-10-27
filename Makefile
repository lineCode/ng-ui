# Travis example for Modern C++ by Rafał Pocztarski
# For more languages and info see:
# https://github.com/rsp/travis-hello#readme

CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

ALL = main

all: $(ALL)

main: main.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

clean:
	$(RM) $(ALL) *.o