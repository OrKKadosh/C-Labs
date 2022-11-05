#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
	char buf;
	int p[2];
	pipe(p);
	if (fork() > 0) {
		close(p[0]);
		write(p[1], "Hello\n", sizeof("Hello\n"));
		close(p[1]);
		wait(NULL);
	}
	else {
		close(p[1]);
		while (read(p[0], &buf, 1) != 0)
 			putchar(buf);
		close(p[0]);
	}
	return 0;
}
