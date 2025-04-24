#include "../minishell.h"

int ft_pwd(t_envrmt **env)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd ");
        exit_value(env, 1);
        return (1);
    }
    else
    {
        printf("%s\n", cwd);
        exit_value(env, 0);
        return (0);
    }
}
