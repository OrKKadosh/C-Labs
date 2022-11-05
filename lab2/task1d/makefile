all: exec

exec: task1d.o
	gcc -m32 -g -Wall -o task1d task1d.o

task1d.o: task1d.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task1d.c -o task1d.o

.PHONY: clean
clean:
	rm -f *.o debug task1d
