all: exec

exec: task1b.o
	gcc -m32 -g -std=c11 -Wall -o task1b task1b.o

task1b.o: task1b.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task1b.c -o task1b.o

debug:
	gcc -g -o debug task1b.c

valg:
	valgrind --leak-check=full task1b.c

.PHONY: clean
clean:
	rm -f *.o debug task1b
