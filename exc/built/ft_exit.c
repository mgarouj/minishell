#include "../minishell.h"

int ft_exit(char **arg, int exit_status)
{
    int i;

    i = 0;
    printf("exit\n");
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
                printf("exit\nminishell: exit: %s numeric argument required\n", arg[1]);
                exit(255);
            }
            i++;
	    }
	    exit(ft_atoi(arg[1]) % 256);
    }
    exit(exit_status);
}