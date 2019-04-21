CFLAGS = -std=c++17 -I ../inc/ -Wall -Wextra -Werror

.PHONY: all clean

_run_tests: *.cc ../inc/cppkit/*.hh ../inc/cppkit/*.h
	c++ $(CFLAGS) -o $@ $(wildcard *_test.cc) $(wildcard *_tests.cc)

clean: *
	rm -f _run_tests
