#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process: Hello!\n");
    } else if (child_pid > 0) {
        // This code is executed by the parent process
        printf("Parent process: Created child with PID %d\n", child_pid);
    } else {
        // fork() failed
        printf("Failed to create child process\n");
        return 1;
    }

    // Both parent and child processes continue execution here

    return 0;
}
