/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:29:32 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/24 11:25:18 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


void handel_heredoc(t_execution *exec,t_tokenn *delimiter)
{
    inf fd[2];
    char *line;

    if(!del)
        return;
    if(pipe(fd) == -1)
    {
        print_err("heredoc error");
        return;
    }
    while(1)
    {
        line =readline("> ");
        if(!line)
            break;
        if(ft_strcmp(line,delimiter->value))
        {
            free(line);
            break;
        }
        write(fd[1],line,ft_strlen(line));
        write(fd[1],"\n",1);
        free(line);
    }
    close(fd[1]);
    if(exec->in_file != 0)
        close(exec->in_file);
    exec->in_file = fd[0];
}

void heredoc(t_tokenn *token,t_execution *exec)
{
    t_tokenn *tmp;
    
    tmp = token;
    while(tmp)
    {
        if(tmp->type == HEREDOC && tmp->next)
            handel_heredoc(exec,tmp->next);
        tmp = tmp->next;
    }
}