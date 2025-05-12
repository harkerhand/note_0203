// time_pipe.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(1);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {                     // 子进程
        close(pipefd[0]); // 关闭读端

        struct timeval current;
        gettimeofday(&current, NULL);

        write(pipefd[1], &current, sizeof(struct timeval));
        close(pipefd[1]);

        // exec command
        execvp(argv[1], &argv[1]);
        perror("exec failed");
        exit(1);
    }
    else
    {                     // 父进程
        close(pipefd[1]); // 关闭写端
        waitpid(pid, NULL, 0);

        struct timeval start, end;
        read(pipefd[0], &start, sizeof(struct timeval));
        close(pipefd[0]);

        gettimeofday(&end, NULL);

        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
        printf("Elapsed time: %.5f seconds\n", elapsed);
    }

    return 0;
}
