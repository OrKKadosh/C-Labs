all: exec

libs: asm-lib c-lib

asm-lib: start.s
	nasm -f elf32 start.s -o start.o

c-lib: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

exec: count.c libs
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector count.c -o count.o
	ld -m elf_i386 start.o count.o util.o -o task1

.PHONY: clean
clean:
	rm -rf ./*.o task1
