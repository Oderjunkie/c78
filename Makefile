all: main

CC = clang
override CFLAGS += -ansi -pedantic -pedantic-errors -g -Wall -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -name 'input' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -name 'input' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o "$@" $(SRCS)

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 -o "$@" $(SRCS)

clean:
	rm -f main main-debug