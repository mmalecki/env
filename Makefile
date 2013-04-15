OBJS += src/env.o

TESTS += test/test-env

CFLAGS=-g -Wall -Iinclude

all: libenv.a

libenv.a: $(OBJS)
	ar rcs $@ $^

src/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@

test/%: test/%.c libenv.a
	gcc -L. -lenv $(CFLAGS) $< -o $@

test: libenv.a $(TESTS)
	test/test-env

clean:
	rm -f libenv.a $(OBJS) $(TESTS)

.PHONY: all test clean
