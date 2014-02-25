OBJS += src/env.o

TESTS += test/test-env

CFLAGS=-g -Wall -Iinclude

all: libenv.a

libenv.a: $(OBJS)
	ar rcs $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test/%: test/%.c libenv.a
	$(CC) $(CFLAGS) -o $@ $< ./libenv.a

test: libenv.a $(TESTS)
	MallocScribble=1 test/test-env

clean:
	rm -f libenv.a $(OBJS) $(TESTS)

.PHONY: all test clean
