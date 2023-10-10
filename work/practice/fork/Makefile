all : forktest forktest2 pipetest

forktest : forktest.c
	gcc forktest.c -o forktest

forktest2 : forktest2.c
	gcc forktest2.c -o forktest2

pipetest : pipetest.c
	gcc pipetest.c -o pipetest

clean:
	rm -f forktest forktest2
