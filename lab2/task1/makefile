all: exec

exec: addresses[1].o
	gcc -m32 -g -Wall -o task1 addresses[1].o

addresses[1].o: addresses[1].c
	gcc -m32 -Wall -c -nostdlib -fno-stack-protector addresses[1].c -o addresses[1].o

debug:
	gcc -g -o debug addresses[1].c

.PHONY: clean
clean:
	rm -f *.o debug task1
