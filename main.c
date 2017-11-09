#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

static void sighandler(int signo){
    if(signo == SIGINT){
		int fd = open("log", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if(fd == -1){
			printf("fd: %d\n", fd);
			printf("errno: %d\n", errno);
			printf("error: %s\n", strerror(errno));
		}
		char msg[] = "Program interrupted\n";
		write(fd, msg, sizeof(msg));
		close(fd);
		exit(0);
    }
	if(signo == SIGUSR1){
		printf("PPID: %d\n", getppid());
    }
}

int main() {
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	while(1){
		printf("%d\n", getpid());
		sleep(1);
	}
	return 0;
}