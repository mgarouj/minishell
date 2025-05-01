/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_shi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:00 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/01 21:01:33 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


int handel_redin(char *filename, t_execution *exec)
{
    int fd = open(filename, O_RDONLY);
    fd_collec(fd, 1);
    if (fd == -1)
    {
        printf("h\n");
        print_err("failed to open fd");
        fd_collec(0, 0);
        return (0);
    }
    if (exec->in_file != 0)
        close(exec->in_file);
    exec->in_file = fd;
    return (1);
}

int handel_reout(char *filename, t_execution *exec)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    fd_collec(fd, 1);
    if (fd == -1)
    {
        print_err("failed to open fd");
        fd_collec(0, 0);
        return (0);
    }
    if (exec->out_file != 1)
        close(exec->out_file);
    exec->out_file = fd;
    return (1);
}

int handel_redappend(char *filename, t_execution *exec)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    fd_collec(fd, 1);
    if (fd == -1)
    {
        print_err("failed to open for append redirection");
        fd_collec(0, 0);
        return (0);
    }
    if (exec->out_file != 1)
        close(exec->out_file);
    exec->out_file = fd;
    return (1);
}
char *get_filename(char *value)
{
    int i = 0;

    if (!value)
        return (NULL);
    while (value[i] && value[i] != ' ' && value[i] != '\t')
        i++;
    return (ft_strldup(value, i));
}

int handel_red(t_tokenn *token, t_execution *exec)
{
    t_tokenn *tmp = token;
    char *filename;

    while (tmp)
    {
        if ((tmp->type == REDIRECTION_IN ||
             tmp->type == REDIRECTION_OUT ||
             tmp->type == REDIRECTION_AP) &&
            tmp->next && tmp->next->type == EXP)
        {
            filename = get_filename(tmp->next->value);
            if (!filename)
                return (0);

            if (tmp->type == REDIRECTION_IN)
            {
                if (!handel_redin(filename, exec))
                    return (0);
            }
            else if (tmp->type == REDIRECTION_OUT)
            {
                if (!handel_reout(filename, exec))
                    return (0);
            }
            else if (tmp->type == REDIRECTION_AP)
            {
                if (!handel_redappend(filename, exec))
                    return (0);
            }

            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    return (1);
}
