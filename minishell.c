#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

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
