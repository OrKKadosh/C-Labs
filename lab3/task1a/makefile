all: exec

exec: task1a.o
	gcc -m32 -g -std=c11 -Wall -o task1a task1a.o

task1a.o: task1a.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task1a.c -o task1a.o

debug:
	gcc -g -o debug task1a.c

valg:
	valgrind --leak-check=full task1a.c

.PHONY: clean
clean:
	rm -f *.o debug task1a
