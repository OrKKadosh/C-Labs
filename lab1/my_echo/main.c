#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	int c;
	printf("my echo: ");
	while (c != EOF){
		c = getchar();
		putchar(c);
	}
	return 0;
}
