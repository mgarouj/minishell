



#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include<unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

enum token
{
    EXP,
    PIPE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    REDIRECTION_IN,
    REDIRECTION_OUT,
    HEREDOC,
};

typedef struct s_tokenn
{
    enum token type;
    char * value;
    struct s_tokenn *next;

} t_tokenn;

typedef struct s_execution
{
    char **cmd;
    int in_file;
    int out_file;
    char **env;
    struct s_execution *next;
} t_execution;

int parssing(char *line);
void print_err(char *str);

#endif