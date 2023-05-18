
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // create a child process
    pid = fork();
    printf("This code demonstrates a zombie process first and then an orphan process");
    if (pid == 0) {
        // child process
        printf("Child process (PID=%d) is sleeping...\n", getpid());
        sleep(10);
        printf("Child process (PID=%d) is exiting...\n", getpid());
        exit(0);
    }
    else if (pid > 0) {
        // parent process
        printf("Parent process (PID=%d) created a child process (PID=%d).\n", getpid(), pid);
        printf("Parent process (PID=%d) is sleeping for 5 seconds...\n", getpid());
        sleep(5);
        printf("Parent process (PID=%d) is exiting...\n", getpid());
        exit(0);
    }
    else {
        // fork failed
        printf("Fork failed!\n");
        exit(1);
    }
    
    return 0;
}

