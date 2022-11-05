all: exec

exec: task3.o
	gcc -m32 -g -Wall -o task3 task3.o

task3.o: task3.c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector task3.c -o task3.o

.PHONY: clean
clean:
	rm -f *.o debug task3
