#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("test", O_RDWR, O_TRUNC);
    if (write(fd, "test\n", 4) == -1)
    {
        printf("error");
    }
    char test[500];
    // close(fd);
    // fd = open("test", O_RDWR);
    // printf("hello world");
    // sleep(5);
    // fsync(fd);
    lseek(fd, 0, SEEK_SET);
    if (read(fd, &test, 4) == -1) //test
    {
        printf("read error");
    }
    test[4] = '\0';
    printf("%s\n", test);
    close(fd);
}
