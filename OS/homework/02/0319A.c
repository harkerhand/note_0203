// time_shm.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define SHM_NAME "/time_shm"
#define SHM_SIZE sizeof(struct timeval)

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(1);
    }

    // 创建共享内存
    // 返回文件描述符
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    // 设置共享内存大小
    ftruncate(shm_fd, SHM_SIZE);
    // 映射共享内存 返回指针
    struct timeval *start_time = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    { // 子进程
        struct timeval current;
        gettimeofday(&current, NULL);
        memcpy(start_time, &current, sizeof(struct timeval));
        // 关闭内存映射
        munmap(start_time, SHM_SIZE);
        // 关闭文件描述符
        close(shm_fd);

        // exec command
        execvp(argv[1], &argv[1]);
        perror("exec failed");
        exit(1);
    }
    else
    { // 父进程
        waitpid(pid, NULL, 0);

        struct timeval end_time;
        gettimeofday(&end_time, NULL);

        // 读取开始时间
        struct timeval start;
        memcpy(&start, start_time, sizeof(struct timeval));

        double elapsed = (end_time.tv_sec - start.tv_sec) + (end_time.tv_usec - start.tv_usec) / 1e6;
        printf("Elapsed time: %.5f seconds\n", elapsed);

        munmap(start_time, SHM_SIZE);
        close(shm_fd);
        shm_unlink(SHM_NAME);
    }

    return 0;
}
