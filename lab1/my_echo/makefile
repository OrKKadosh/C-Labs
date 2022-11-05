all: exec

exec: main.o
	gcc -m32 -g -Wall -o my_echo main.o

main.o: main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o


.PHONY: clean
clean:
	rm -f *.o my_echo
