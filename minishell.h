/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:18 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/11 18:10:43 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef MINISHELL_H
#define MINISHELL_H

# define MALLOC_ERORR "allocation failed\n"
# define SYNTAX_ERROR_PIPE "syntax error near unexpected token `|'\n"
# define SYNTAX_ERROR_QUOTE "syntax error missing quote\n"
# define SYNTAX_ERROR_REDIRECTION "syntax error near unexpected token `>'\n"
# define SYNTAX_ERROR_REDIRECTION_2 "syntax error near unexpected token `>>'\n"
# define FILE_D_ERROR_FAIL "faild to open fd\n"


#include <stdlib.h>
#include<unistd.h>
#include <stdbool.h>
#include <stdio.h> 
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

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}t_env;

typedef struct s_execution
{
    char **cmd;
    int in_file;
    int out_file;
    char **env;
    struct s_execution *next;
} t_execution;


typedef struct s_gc
{
    void    *ptr;
    bool    is_free;
    struct s_gc *next;
}t_gc;


int parssing(char *line);
void print_err(char *str);
char *ft_strtrim(char *s, int size);
int ft_strlen(char const *str);
char *ft_strndup(char *s, size_t n);
t_tokenn *tokenize(char *line);
void handel_env(char *s,t_env **env);

//utils

char **ft_split(char *, char );

#endif