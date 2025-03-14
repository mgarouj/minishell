

#include "../minishell.h"

void print_err(char *str)
{
    int i;

    i = 0;
    write(2,"error :",7);
    while(str[i])
    {
        write(2,&str[i],1);
        i++;
    }
    write(2,"\n",1);
}