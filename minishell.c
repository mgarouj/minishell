#include "minishell.h"

#include <stdio.h>


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char *line;
    while (line = readline("minishell>>"))
    {
        // parsing
    }
}
