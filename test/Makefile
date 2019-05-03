CFLAGS = -std=c++17 -g -I ../inc/ -Wall -Wextra -Werror

.PHONY: all clean

all: _run_tests

_run_tests: *.cc ../inc/cppkit/*.hh ../inc/cppkit/*.h
	c++ $(CFLAGS) -o $@ $(wildcard *_test.cc) $(wildcard *_tests.cc) `pkg-config --cflags --libs eigen3`

clean: *
	rm -f _run_tests
