#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Demonstrate fork()
void demo_fork() {
    pid_t process_id;
    process_id = fork();
    
    if (process_id == 0) {
        printf("Child process (PID=%d) created!\n", getpid());
        exit(0);
    }
    else if (process_id > 0) {
        printf("Parent process (PID=%d) created a child process (PID=%d).\n", getpid(), process_id);
    }
    else {
        printf("Fork failed!\n");
    }
}

// Demonstrate exit()
void demo_exit() {
    printf("Before exit()\n");
    exit(0);
    printf("After exit()\n"); // This line will not be executed
}

// Demonstrate kill()
void demo_kill() {
    pid_t process_id;
    process_id = fork();
    
    if (process_id == 0) {
        printf("Child process (PID=%d) created!\n", getpid());
        sleep(5);
        printf("Child process (PID=%d) is exiting...\n", getpid());
        exit(0);
    }
    else if (process_id > 0) {
        printf("Parent process (PID=%d) created a child process (PID=%d).\n", getpid(), process_id);
        sleep(2);
        printf("Parent process (PID=%d) sending SIGTERM signal to child process (PID=%d).\n", getpid(), process_id);
        kill(process_id, SIGTERM);
        wait(NULL);
        printf("Child process (PID=%d) has been terminated.\n", process_id);
    }
    else {
        printf("Fork failed!\n");
    }
}

// Demonstrate exec()
void demo_exec() {
    pid_t process_id;
    process_id = fork();
    
    if (process_id == 0) {
        printf("Child process (PID=%d) created!\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
        printf("This line will not be executed.\n");
        exit(0);
    }
    else if (process_id > 0) {
        printf("Parent process (PID=%d) created a child process (PID=%d).\n", getpid(), process_id);
        wait(NULL);
    }
    else {
        printf("Fork failed!\n");
    }
}

// Demonstrate wait()
void demo_wait() {
    pid_t process_id;
    process_id = fork();
    
    if (process_id == 0) {
        printf("Child process (PID=%d) created!\n", getpid());
        sleep(5);
        printf("Child process (PID=%d) is exiting...\n", getpid());
        exit(0);
    }
    else if (process_id > 0) {
        printf("Parent process (PID=%d) created a child process (PID=%d).\n", getpid(), process_id);
        wait(NULL);
        printf("Child process (PID=%d) has been terminated.\n", process_id);
    }
    else {
        printf("Fork failed!\n");
    }
}

// Demonstrate sleep()
void demo_sleep() {
    printf("Sleeping for 5 seconds...\n");
    sleep(5);
    printf("Done sleeping.\n");
}

int main() {
    printf("Demo fork()\n");
    demo_fork();
    
    
    printf("\nDemo kill()\n");
    demo_kill();
    
    printf("\nDemo exec()\n");
    demo_exec();
    
    printf("\nDemo wait()\n");
    demo_wait();
    
    printf("\nDemo sleep()\n");
    demo_sleep();
    

    printf("\nDemo exit()\n");
    demo_exit();
    return 0;
}
