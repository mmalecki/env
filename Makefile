OBJS += src/env.o

TEST_OBJS += test/test-env

CFLAGS=-g -Wall -Iinclude

all: libenv.a

libenv.a: $(OBJS)
	ar rcs $@ $^

src/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@

test/%: test/%.c
	gcc -L. -lenv $(CFLAGS) $< -o $@

test: libenv.a $(OBJS) $(TEST_OBJS)
	test/test-env

clean:
	rm -f libenv.a
	rm -f $(OBJS)
