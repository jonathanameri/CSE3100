CLI = client.o
SRV = server.o
OBJS = 
CFLAGS = -g

all : client1 server1

client: $(CLI) $(OBJS)
	gcc $(CFLAGS) $(LFLAGS) -o client $(CLI) $(OBJS)

server: $(SRV) $(OBJS)
	gcc $(CFLAGS) $(LFLAGS) -o server $(SRV) $(OBJS)

clean:
	rm -rf *.o client server *~
