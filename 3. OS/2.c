#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        // wait(NULL);
        for (int i = 6; i <= 10; i++)
        {
            printf("Child: %d\n", i);
        }
    }
    else
    {
        // Parent process
        // wait(NULL);
        for (int i = 1; i <= 5; i++)
        {
            printf("Parent: %d\n", i);
        }
    }

    return 0;
}