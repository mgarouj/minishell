#include "../minishell.h"

pid_t ft_fork(const char *msg)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return (pid);
}