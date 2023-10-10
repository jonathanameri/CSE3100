CFLAGS = -Wall -o
all : readwrite data-gen

readwrite : readwrite.c
	gcc readwrite.c $(CFLAGS) readwrite

data-gen : data-gen.c
	gcc data-gen.c $(CFLAGS) data-gen
make clean :
	rm -f readwrite data-gen
