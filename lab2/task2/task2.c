#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char censor(char c);
char* map(char *array, int array_length, char (*f) (char));
char encrypt(char c); 
char decrypt(char c);
char dprt(char c);
char cprt(char c); 
char my_get(char c);
char quit(char c)


char censor(char c) {
	if(c == '!')
		return '*';
	else
		return c;
}

char* map(char *array, int array_length, char (*f) (char)){
	char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
	for (int i = 0; i < array_length; i++){
		mapped_array[i] = f(array[i]);
	}
	return mapped_array;
}

int main(int argc, char **argv){
	


//	char arr1[] = {'H','e','y','!'};
//	char* arr2 = map(arr1, 4, my_get);
//	printf("%s\n", arr2);
//	char* arr2 = map(arr1, 4, encrypt);
//	printf("%s\n", arr2);
//	char* arr3 = map(arr2, 4, decrypt);
//	printf("%s\n", arr3);
//	free(arr2);
//	free(arr3);
}
/* Gets a char c and returns its encrypted form by adding 2 to its value. If c is not between 0x41 and 0x7a it is returned unchanged */
char encrypt(char c){
	if (&c < 0x41 || &c > 0x77){
		return c+2;
	}
	else{
		return c;
	}
}

/* Gets a char c and returns its decrypted form by reducing 2 to its value. If c is not between 0x41 and 0x7a it is returned unchanged */
char decrypt(char c){
	if (&c < 0x41 || &c > 0x77){
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
	if (&c < 0x41 || &c > 0x77){
		printf("%s\n", "*");
		return c;
	}
	else{
		printf("%d\n", c);
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


