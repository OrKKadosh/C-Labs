#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    unsigned char* sig;
    char virusName[16];
} virus;



void readVirus(virus* vir, FILE* input){
	//05 00 31 32 33 34 35 56 49 52 55 53 00 00 00 00 00 00 00 00 00 00 00	
	if (fread(vir, 1, 2, input) != 0){
		vir->sig = malloc(vir->SigSize);
		fread(vir->sig, 1, vir->SigSize, input);
		fread(vir->virusName, 1, 16, input);
	}
}

int getNum(){
	return 11;
}

void printVirus(virus* vir, FILE* output){
	fprintf(output,"virus name: %s\n", vir->virusName);
	fprintf(output,"virus size: %d\n", vir->SigSize);
	fprintf(output,"signature:\n");
	PrintHex(output, vir->sig, vir->SigSize);
}

void PrintHex(FILE* output, unsigned char* buffer,unsigned short length) {
	for (int i = 0; i < length; i++){
		fprintf(output,"%02hhX ", buffer[i]);
	}
	fprintf(output,"\n\n");
}



int main(int argc, char** argv){
	FILE* input = fopen(argv[1], "r");
	FILE* output = stdout;
	output = fopen("output.txt", "w");
	if (input == NULL){
		fprintf(stderr, "Could not read file\n");
		exit(1);
	}
	int numOfVirs = getNum();
	for (int i = 0; i < numOfVirs; i++){
		virus* myVirus = malloc(sizeof(struct virus));
		readVirus(myVirus, input);
		printVirus(myVirus, output);
		free(myVirus->sig);
		free(myVirus);
	}
	fclose(input);
	fclose(output);
	return 0;
}









