#include <stdio.h>
#include <unistd.h>

int main(){
	char* arg[] = {"cat" , "in.txt" , " | " , " sed 's/hi/hello/g'" , NULL};
	execvp(arg[0] , arg);
	return 0;
}
