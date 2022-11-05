#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    unsigned char* sig;
    char virusName[16];
} virus;

typedef struct link link;
struct link {
    link *nextVirus;
    virus *vir;
};

struct newMenu{
    char *name;
    link* (*fun)(link*);
};
 
link* newLink(virus* data){
	link* newLink = malloc(sizeof(struct link));
	newLink->vir = data;
	newLink->nextVirus = NULL;
	return newLink;
}


int getNum(){
	return 11;
}



void PrintHex(FILE* output, unsigned char* buffer,unsigned short length) {
	for (int i = 0; i < length; i++){
		fprintf(output,"%02hhX ", buffer[i]);
	}
	fprintf(output,"\n\n");
}

link* quit(link* link){
	list_free(link);
	exit(0);
}



void list_free(link *virus_list){
	link* currLink = virus_list;
	if(currLink != NULL){
		list_free(currLink->nextVirus);
		free(currLink->vir->sig);
		free(currLink->vir);
		free(currLink);
	}
}

void readVirus(virus* vir, FILE* input){
	if (fread(vir, 1, 2, input) != 0){
		vir->sig = malloc(vir->SigSize);
		fread(vir->sig, 1, vir->SigSize, input);
		fread(vir->virusName, 1, 16, input);
	}
}

link* list_append(link* virus_list, link* to_add){
	if (virus_list == NULL){
		virus_list = to_add;
	}
	else{
		virus_list->nextVirus = list_append(virus_list->nextVirus, to_add);
	}
	return virus_list;
}

link* load_list(FILE* file){
	link* head = NULL;
	int numOfVirs = getNum();
	FILE* out = fopen("output.txt", "w");
	for (int i = 0; i < numOfVirs; i++){
		virus* myVirus = malloc(sizeof(struct virus));
		readVirus(myVirus, file);
		link* myFuckingLink = newLink(myVirus);
		head = list_append(head, myFuckingLink);
	}
	fclose(file);
	return head;
}

link* load_signatures(link* link){
	char* fileName = NULL;
	char buf[BUFSIZ];
	printf("Enter signature file name:\n");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%ms", &fileName);
	
	FILE* file = fopen(fileName,"rb");
	
	free(fileName);

	if(file == NULL){
		fprintf(stderr, "Reading File Error\n");
		exit(1);
	}
	return load_list(file);
}

void printVirus(virus* vir, FILE* output){
	fprintf(output,"virus name: %s\n", vir->virusName);
	fprintf(output,"virus size: %d\n", vir->SigSize);
	fprintf(output,"signature:\n");
	PrintHex(output, vir->sig, vir->SigSize);
}

void list_print(link *virus_list, FILE* input){
	link* currLink = virus_list;
	while (currLink != NULL){
		printVirus(currLink->vir, input);
		currLink = currLink->nextVirus;
	}
}

link *print_signatures(link *list){
	list_print(list, stdout);
	return list;
}

int main(int argc, char **argv) {
	link* list = NULL;
	struct newMenu menu[] = {{"Load signatures",load_signatures},{"Print signatures",print_signatures},{"Quit", quit},{NULL, NULL}};
	int bounds = sizeof(menu) / (sizeof(struct newMenu))-1;
	int option;
	while (1){
		printf("Please choose a function:\n");
		for (int i = 0; i < bounds; i++){
			printf("%d) %s\n", i + 1, menu[i].name);
		}
		printf("Option: ");
		scanf("%d", &option);
		fgetc(stdin);
		if (option < 1 || option > bounds){
			printf("Not within bounds\n");
			exit(1);
		}
		else{
			list = menu[option-1].fun(list);
			printf("\n");
		}
	}
	free(list);
	return 0;
}
