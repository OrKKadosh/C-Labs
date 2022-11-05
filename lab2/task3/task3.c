#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct fun_desc {
	char *name;
	char (*fun)(char);
};

char* map(char *array, int array_length, char (*f) (char)){
	char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  	for(int i = 0; i < array_length; i++){
    		mapped_array[i]=f(*(array+i));
  	}
  	return mapped_array;
}

char censor(char c) {
	if(c == '!')
		return '*';
	else
		return c;
}

/* Gets a char c and returns its encrypted form by adding 2 to its value. If c is not between 0x41 and 0x7a it is returned unchanged */
char encrypt(char c){
	if (c >= 0x41 && c <= 0x77){
		return c+2;
	}
	else{
		return c;
	}
}

/* Gets a char c and returns its decrypted form by reducing 2 to its value. If c is not between 0x41 and 0x7a it is returned unchanged */
char decrypt(char c){
	if (c >= 0x41 && c <= 0x77){
		return c-2;
	}
	else{
		return c;
	}
}

/* dprt prints the value of c in a decimal representation followed by a new line, and returns c unchanged. */
char dprt(char c){
	printf("%d\n", c);
	return c;
}

/* If c is a number between 0x41 and 0x7a, cprt prints the character of ASCII value c followed by a new line. 
Otherwise, cprt prints the dot ('*') character. After printing, cprt returns the value of c unchanged. */
char cprt(char c){
	if (c >= 0x41 && c <= 0x77){
		printf("%c\n", c);
		return c;
	}
	else{
		printf("*\n");
		return c;
	}
}

 /* Ignores c, reads and returns a character from stdin using fgetc. */
char my_get(char c){
	FILE* in = stdin;
	int c_from_stdin = fgetc(in);
	if (c_from_stdin != EOF){
		if (c_from_stdin != 10){
			return c_from_stdin;
		}
	}
}

/* Gets a char c,  and if the char is 'q' , ends the program with exit code 0. Otherwise returns c. */
char quit(char c){
	if (c == 'q'){
		exit(0);
	}
	return c;
}

int main(int argc, char **argv){
	
	
	char* carray = (char*)(malloc(5*sizeof(char)));
	char buf[BUFSIZ];
	int opt;
	struct fun_desc menu[] = {{"Censor",&censor },{"Encrypt",&encrypt},{"Decrypt",&decrypt},{"Print dec",&dprt},
				  {"Print string",&cprt},{"Get string",&my_get},{"Quit",&quit},{NULL,NULL}};
	int bounds = sizeof(menu) / (sizeof(struct fun_desc))-1;
	while(1){
		printf("Please choose a function:\n");
		for (int i = 0; i < bounds; i++){
			printf("%d) %s\n", i, menu[i].name);
		}
		printf("Option: ");
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", &opt);
		if ( (opt < 0) || (opt > bounds - 1) ){
			printf("Not within bounds\n");
			exit(1);
		}
		else{
			printf("Within bounds\n");
			char* tmp = map(carray, 5, menu[opt].fun);
			carray = tmp;
			printf("%s\n", carray);
			printf("DONE.\n\n");
			free(tmp);
		}
	}
	free(carray);
}



