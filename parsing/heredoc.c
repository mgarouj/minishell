/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:29:32 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/23 18:35:01 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


void handel_heredoc(t_execution *exec,char *del)
{
    inf fd[2];
    char *line;

    if(!del)
        return;
    if(!pipe(fd))
    {
        print_err("heredoc error");
        return;
    }
    while(1)
    {
        
    }
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