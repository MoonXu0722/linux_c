#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char buf[256];
	char *msg = "child write hello pipe\n";
	int pipefd[2];
	int fd = pipe(pipefd);
	if(fd == -1) {
		perror("pipe");
		return -1;
	}
	pid_t pid = fork();
	if(pid == -1) {
		perror("fork");
		return -1;
	}
#if 0
	if(pid == 0) {
		close(pipefd[1]);
		int r = read(pipefd[0], buf, r);
		write(1, buf, r);
		exit(0);
	} else {
		close(pipefd[0]);
		write(pipefd[1], msg, strlen(msg));
		wait(NULL);
	}
#endif
	if(pid == 0) {
		close(pipefd[0]);
		write(pipefd[1], msg, strlen(msg));
		exit(0);
	} else {
		close(pipefd[1]);
		int r = read(pipefd[0], buf, r);
		write(1, buf, r);
		wait(NULL);
	}
	return 0;
}
