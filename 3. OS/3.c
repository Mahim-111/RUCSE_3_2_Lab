#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid1, pid2;

    // First fork → creates first child
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("Fork 1 failed");
        return 1;
    }

    if (pid1 == 0)
    {
        // First child process
        printf("First Child:\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else
    {
        // Only parent executes second fork
        pid2 = fork();

        if (pid2 < 0)
        {
            perror("Fork 2 failed");
            return 1;
        }

        if (pid2 == 0)
        {
            // Second child process
            printf("Second Child:\n");
            printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
        }
        else
        {
            // Parent process
            printf("Parent:\n");
            printf("PID: %d\n", getpid());
            printf("Child1 PID: %d\n", pid1);
            printf("Child2 PID: %d\n", pid2);
        }
    }

    return 0;
}