#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv){

	int iarray[3];
	float farray[3];
	double darray[3];
	char carray[3];
//int - 12
	printf("- &iarray  : %d\n",iarray);
	printf("- &iarray+1: %d\n",iarray+1);
	printf("\n");

//float - 12
    	printf("- &farray  : %d\n",farray);
	printf("- &farray+1: %d\n",farray+1);
	printf("\n");

//double - 24
    	printf("- &darray  : %d\n",darray);
	printf("- &darray+1: %d\n",darray+1);
	printf("\n");

//char - 2
    	printf("- &carray  : %d\n",carray);
	printf("- &carray+1: %d\n",carray+1);
	printf("\n");
}
