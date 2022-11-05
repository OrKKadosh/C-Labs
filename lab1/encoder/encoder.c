#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encoder1c(FILE* in, FILE* out, int repeat, int sign);
void encoder1b(FILE* in, FILE* out);
void encoder1a(FILE* in, FILE* out);
int converToDecimal(char a);

int main(int argc, char** argv){
	FILE * in = stdin;
	FILE * out = stdout;
	char argvBuf[256];
	int debug = 0;
	int e = 0;
	int repeat = 0;
	int sign = 0;
	int i;

	if (argc >= 2){
		for (i = 1; i < argc; i++){	
			if (strncmp(argv[i], "-D", 2) == 0){
				debug = 1;
				printf("debug parsed");
				printf("\n");
			}
			if (strncmp(argv[i], "+e", 2) == 0){
				e = 1;
				sign = 1;
				memcpy(argvBuf, &argv[i][0], 3);
				printf("e pos parsed");
				printf("\n");
			}
			if (strncmp(argv[i], "-e", 2) == 0){
				e = 1;
				sign = 0;
				memcpy(argvBuf, &argv[i][0], 3);
				printf("e neg parsed");
				printf("\n");
			}
			if (strncmp(argv[i], "-i", 2) == 0){
				printf("file parsed");
				printf("\n");
				in = fopen(argv[i]+2,"r");
				if (in == NULL){
					fprintf(stderr, "there is no input file\n");
					return 1;
				}
			}
			if (strncmp(argv[i], "-o", 2) == 0){
				out = fopen(argv[i]+2,"w");
				printf("output parsed");
				printf("\n");
			}
		}
	}
	if(e > 0){
		repeat = converToDecimal(argvBuf[2]);
		encoder1c(in, out, repeat, sign);
	}
	else{
		if (debug == 1){
			encoder1b(in, out);
		}
		else{
			encoder1a(in, out);
		}
	}
	return 0;	
}
	
void encoder1c(FILE* in, FILE* out, int repeat, int sign){
	char c = '\0';
	char first = '\0';
	int taken = 0;
	int i;

	printf("encode1c\n");
	printf("enter a string:\n");
	while((c = fgetc(in)) != EOF){
		if (taken == 0){
			first = c;
			taken = 1;
		}
		if (sign > 0){
			if(c != 10){
				fprintf(out, "%c", c);
			}
			else{
				for(i = 0; i < repeat; i++){
					fprintf(out, "%c", first);
				}
				printf("\n");
			}
		}
		else{
			if(c != 10){
				if (repeat > 0){
					repeat--;
				}
				else{
					fprintf(out, "%c", c);
				}
			}
			else{
				if(repeat > 0){
					fprintf(out, "%s", "-NONE-");
				}
			}
		}
	}					
}

void encoder1b(FILE* in, FILE* out){
	char c = '\0';
	int counter = 0;
	printf("encode1b\n");
	printf("enter a string:\n");
	while((c = fgetc(in)) != EOF){
		if(c != 10){
			fprintf(stderr, "%d", c);
			if ( (c < 91) && (c > 64) ){//hardcoded numbers
				c = '.';
				counter++;
			}
			fputc(c, out);
			fprintf(stderr, "\t%d\n", c);
		}
		else{
			printf("\n");
			printf("letters encoded: ");
			printf("%d",counter);
			printf("\n");
		}
	}
}
	

void encoder1a(FILE* in, FILE* out){
	int c;
	int d;
	printf("encode1a\n");
	printf("enter a string:\n");
	c = fgetc(in);
	while(c != EOF){
		if(c != 10){
			d = c;
			if ((c <= 'Z') && (c >= 'A')){
				d = '.';
			}
			fputc(d, out);
			c = fgetc(in);
			d = c;
		}
		else{
			c = fgetc(in);
			printf("\n");
		}
	}
}
int converToDecimal(char a){
	if (a >= '0' && a <= '9'){
		return a - '0';
	}
	else{
		return a + 10 - 'A';
	}
	
	return 0;
}






