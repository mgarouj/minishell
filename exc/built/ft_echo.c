#include "../minishell.h"

// echo command if -nnnnnnnn print the flag without the \n -nnnnnnnnf print the flag with \n

bool check_flag(char *flag)
{
    int i;

    i = 0;
    if (flag[i] != '-')
        return (0);
    i++;
    while(flag[i])
    {
        if (flag[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void print_arg(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i + 1])
            printf("%s ", arg[i]);
        else 
            printf("%s", arg[i]);
        i++;
    }
}

int ft_echo(char **arg)
{
    int i;
    bool flag;

    i = 1;
    if (!arg[1])
    {
        printf("\n");
        return (1);
    }
    if (check_flag(arg[i]))
    {
        flag = 1;
        i++;
    }
    else
        flag = 0;
    print_arg(arg + i);
    return (0);
}

