#include "../minishell.h"

void	print_error_env(char *arg)
{
	write(2, "env: ", 5);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
}


int ft_env(char **arg, t_env **env)
{
    t_env *tmp;

    tmp = *env;
    if (!get_env_value("PATH", *env))
    {
        write(2, "env: No such file or directory\n", 31);
		return (1);
    }
    if (arg[1])
    {
        print_error_env(arg[1]);
        return (127);
    }
    while (tmp)
	{
        ft_3putstr(tmp->key, "=", tmp->value, "\n");
		tmp = tmp->next;
	}
	return (0);
}