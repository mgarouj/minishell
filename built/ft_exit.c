#include "../minishell.h"

int ft_exit(char **arg, int exit_status)
{
    int i;

    i = 0;
    ft_putstr_fd("exit\n", 1);
    if (arg[0] && arg[1] && arg[2])
    {
        printf("minishell: exit: too many arguments\n");
        return (1);
    }
    if (arg[1])
    {
        if (arg[1][0] == '-' || arg[1][0] == '+')
			i++;
        while (arg[i])
        {
            if (!(arg[1][i] >= '0' && arg[1][i] <= '9'))
            {
                ft_3putstr("exit\nminishell: exit: ", arg[1], " numeric argument required\n", NULL);
                exit(255);
            }
            i++;
	    }
	    exit(ft_atoi(arg[1]) % 256);
    }
    exit(exit_status);
}