all: exec

exec: task2a.o
	gcc -m32 -g -std=c11 -Wall -o task2a task2a.o

task2a.o: task2a.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task2a.c -o task2a.o

debug:
	gcc -g -o debug task2a.c

valg:
	valgrind --leak-check=full task2a.c

.PHONY: clean
clean:
	rm -f *.o debug task2a
