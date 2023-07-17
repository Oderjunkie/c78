all : main

CFLAGS := -std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wno-missing-parameter-type -Wno-return-type -Wno-implicit-int
sources := $(wildcard ./*.c)

include $(sources:.c=.d)

%.d : %.c
	$(CC) $(CFLAGS) -M $^ > $@
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
main : $(sources:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^
clean :
	rm *.o *.d
