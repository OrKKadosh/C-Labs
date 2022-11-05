all: exec

exec: task1c.o
	gcc -m32 -g -std=c11 -Wall -o task1c task1c.o

task1c.o: task1c.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task1c.c -o task1c.o

debug:
	gcc -g -o debug task1c.c

valg:
	valgrind --leak-check=full task1c.c

.PHONY: clean
clean:
	rm -f *.o debug task1c
