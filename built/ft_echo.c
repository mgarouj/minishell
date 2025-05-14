#include "../minishell.h"


bool check_flag(char *flag)
{
    int i;

    i = 0;
    if (!flag || flag[i] != '-')
        return false;
    i++;
    while (flag[i])
    {
        if (flag[i] != 'n')
            return false;
        i++;
    }
    return true;
}

void print_args(char **args, bool newline)
{
    int i = 0;

    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd("\n", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
}

int ft_echo(char **args)
{
    int i = 1;
    bool n_flag;

    n_flag = false;
    if (!args[1])
    {
        ft_putstr_fd("\n", 1);
        return 0;
    }

    if (check_flag(args[i]))
    {
        n_flag = true;
        i++;
    }

    print_args(args + i, !n_flag);
    return 0;
}

