#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv){

	int iarray[] = {1,2,3};
	char carray[] = {'a','b','c'};
	int* iarrayPtr;
	char* carrayPtr;
	

	iarrayPtr = &iarray[0];
	carrayPtr = &carray[0];
	
	printf("- &iarray   : %p\n",&iarray);
	printf("- &iarrayPtr: %p\n",iarrayPtr);
	printf("\n");
    	printf("- &carray   : %p\n",&carray);
	printf("- &carrayPtr: %p\n",carrayPtr);
	printf("\n");
}
