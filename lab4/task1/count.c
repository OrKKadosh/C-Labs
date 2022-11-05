#include "util.h"

#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define SEEK_SET 0

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDRW 2
#define O_CREATE 64

#define STDIN 0
#define STDOUT 1
#define STDERR 2

extern int system_call();

int main (int argc , char* argv[], char* envp[]){
  
	int input = STDIN;
	int output = STDOUT;

	int isLetter;
	char nextChar;
	int debug = 0;
	int i;
	char *name;
	int numOfWords = 0;

	int checkFile;

	for(i = 1; i < argc; i++){
		if((strcmp("-D", argv[i]) == 0)){
			debug = 1;
		}
		else{
			if(strncmp(argv[i], "-i", 2) == 0){
				int inputFile;
				name = argv[i] + 2;
				inputFile = system_call(SYS_OPEN, name, O_RDONLY, 0777);
				if(inputFile <= 0)
					system_call(SYS_EXIT,0x55, 0, 0);
				input = inputFile;
			}
			else {
				if(strncmp(argv[i], "-o", 2) == 0){
					int outputFile;
					name = argv[i] + 2;
					outputFile = system_call(SYS_OPEN, name, O_WRONLY | O_CREATE, 0777);
					if(outputFile <= 0)
						system_call(SYS_EXIT,0x55, 0, 0);
					output = outputFile;
				}
				else{
					system_call(SYS_EXIT,0x55, 0, 0);
				}
			}
		}
	}

	while(checkFile = system_call(SYS_READ, input, &nextChar, 1)){
		if(checkFile <= 0 || nextChar != '\n'){
			if(!debug){
				if(checkFile <= 0){
					system_call(SYS_EXIT,0x55, 0, 0);
        			}
				if((nextChar >= 'A' && nextChar <= 'Z') || (nextChar >= 'a' && nextChar <= 'z')){
		  			isLetter = 1;
				}
				else{
					if (nextChar == ' ' || nextChar == '\n'){
						if (isLetter == 1){
							numOfWords++;
							isLetter = 0;
						}
					}
				}
      			}
      			if(debug){
				system_call(SYS_WRITE, STDERR, itoa(SYS_READ), strlen(itoa(SYS_READ)));
				system_call(SYS_WRITE, STDERR, "\t", 1);
				system_call(SYS_WRITE, STDERR, itoa(input), strlen(itoa(input)));
				system_call(SYS_WRITE, STDERR, "\t", 1);
				system_call(SYS_WRITE, STDERR, itoa(nextChar), strlen(itoa(nextChar)));
				system_call(SYS_WRITE, STDERR, "\t", 1);
				system_call(SYS_WRITE, STDERR, itoa(output), strlen(itoa(output)));
				system_call(SYS_WRITE, STDERR, "\t", 1);
				system_call(SYS_WRITE, STDERR, itoa(checkFile), strlen(itoa(checkFile)));
				system_call(SYS_WRITE, STDERR, "\n", 1);
        			if(checkFile <= 0){
          				system_call(SYS_EXIT,0x55, 0, 0);
        			}
				
				
				if((nextChar >= 'A' && nextChar <= 'Z') || (nextChar >= 'a' && nextChar <= 'z')){
					isLetter = 1;

				}
        			else{
					if (nextChar == ' ' || nextChar == '\n'){
						if (isLetter == 1){
							numOfWords++;
							isLetter = 0;
						}
					}
					
				}
				if(checkFile <= 0){
					system_call(SYS_EXIT,0x55, 0, 0);
				}
			}
		}
		else{
			system_call(SYS_WRITE, output, "\n", 1);
		}
	}

	if(debug){
		system_call(SYS_WRITE, output, "The number of words: ", strlen("\nthe number of words: "));
		if (isLetter)
			numOfWords++;
		checkFile = system_call(SYS_WRITE, output, itoa(numOfWords), strlen(itoa(numOfWords)));
		system_call(SYS_WRITE, output, "\n", 1);


		system_call(SYS_WRITE, STDERR, itoa(SYS_WRITE), strlen(itoa(SYS_WRITE)));
		system_call(SYS_WRITE, STDERR, "\t", 1);
		system_call(SYS_WRITE, STDERR, itoa(output), strlen(itoa(output)));
		system_call(SYS_WRITE, STDERR, "\t", 1);
		system_call(SYS_WRITE, STDERR, itoa(numOfWords), strlen(itoa(nextChar)));
		system_call(SYS_WRITE, STDERR, "\t", 1);
		system_call(SYS_WRITE, STDERR, itoa(1), strlen(itoa(1)));
		system_call(SYS_WRITE, STDERR, "\t", 1);
		system_call(SYS_WRITE, STDERR, itoa(checkFile), strlen(itoa(checkFile)));
		system_call(SYS_WRITE, STDERR, "\n", 1);
	}
	else{
		if (isLetter)
			numOfWords++;
		system_call(SYS_WRITE, output, "The number of words: ", strlen("\nthe number of words: "));
		system_call(SYS_WRITE, output, (numOfWords),1);
		system_call(SYS_WRITE, output, "\n", 1);	
	}

	system_call(SYS_CLOSE, input, 0, 0);
	system_call(SYS_CLOSE, output, 0, 0);
	return 0;
}
