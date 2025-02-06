#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void inside_child(int *current, int *parent)
{
    if (*current == *parent + 1)
        printf("[You are inside the child process] \n");
    else
        printf("[You are not inside the child process]\n");
}

int main()
{
    int parent = getpid();
    printf("starting prog ... \n");
    printf("parent prog id => %d\n", parent);
    int child = fork();
    printf("child state is => %d \n", child);
    int exec_stat;

    if (child == 0)
    {
        int current = getpid();
        inside_child(&current, &parent);
        char *args[] = {"grep", "main", "test.l", NULL};
        exec_stat = execvp("grep", args);
        perror("execvp failed");
        exit(1);
    }
    int result = waitpid(child, NULL, 0);
    printf("%d\n",exec_stat);
    printf("%d\n", result); 
    return 0;
}
