CFLAGS = -std=c++17 -Wall -Wextra -Werror

.PHONY: all clean

_run_tests: *.cc *.hh *.h
	c++ $(CFLAGS) -o $@ $(wildcard *_test.cc) $(wildcard *_tests.cc)

clean: *
	rm -f _run_tests
