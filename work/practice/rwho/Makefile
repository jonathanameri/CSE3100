CLI = rwho.o
SRV = rwhod.o
CFLAGS = -g

all: rwho rwhod

rwho: rwho.o 
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

rwhod: rwhod.o
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	rm -rf *.o rwho rwhod  *~
