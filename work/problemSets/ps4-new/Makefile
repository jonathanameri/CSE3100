TARGETS=mygrep data-extract data-gen
SRCS=$(patsubst %,%.c,$(TARGETS))
CC=gcc
CFLAGS= -Wall -g

all : $(TARGETS)

$(TARGETS): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	@rm -f $(TARGETS) *.o a.out

ultraclean: clean
	@rm -f *.dat

sub: 
	@zip $${PWD##*/}.zip $(SRCS) Makefile

test1:
	./data-gen 3100 100 a.dat
	xxd -g4 a.dat
	./data-extract a.dat t2.dat 1-99 0
	xxd -g4 t2.dat
