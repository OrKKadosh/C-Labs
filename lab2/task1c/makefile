all: exec

exec: task1c.o
	gcc -m32 -g -Wall -o task1c task1c.o

task1c.o: task1c.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task1c.c -o task1c.o

.PHONY: clean
clean:
	rm -f *.o debug task1c
