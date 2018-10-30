#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// ls | sort

int main(int argc, char** argv)
{
	int tubo[2];
	pipe(tubo);

	pid_t p1;

	p1  = fork(); 

	if (p1 != 0) { // padre
		dup2(tubo[0], STDIN_FILENO);
		close(tubo[1]);
		execlp("sort", "sort", "-r", NULL);
		close(tubo[0]);
	} else { // hijo
		dup2(tubo[1], STDOUT_FILENO);
		close(tubo[0]);
		execlp("ls", "ls", NULL);
		close(tubo[1]);
	}
	return 0;
}
