#include "../minishell.h"

int ft_pwd(t_env **env)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd ");
        set_exit_status(env, 1);
        return (1);
    }
    else
    {
        ft_3putstr(cwd, "\n", NULL, NULL);
        set_exit_status(env, 0);
        return (0);
    }
}
