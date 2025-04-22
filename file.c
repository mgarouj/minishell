

#include "minishell.h"

int main()
{
    int fd;
    int fd1;

    fd = open("hello", O_RDONLY);
    if(fd == -1)
    {
        printf("failed to open fd");
        return 0;
    }
    printf("%d\n",fd);
    close(fd);
    fd1 = open("hello", O_RDONLY);
    if(fd1 == -1)
    {
        printf("failed to open fd");
        return 0;
    }
    printf("%d\n",fd1);
}