all: MyShell

MyShell: MyShell.o LineParser.o procs.o
	gcc MyShell.o LineParser.o procs.o -o MyShell
MyShell.o: MyShell.c
	gcc -c -Wall -g MyShell.c -o MyShell.o
LineParser.o: LineParser.c
	gcc -c -Wall -g LineParser.c -o LineParser.o
procs.o: procs.c
	gcc -c -Wall -g procs.c -o procs.o


.PHONY: clean
clean:
	rm *.o MyShell
