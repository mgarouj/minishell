/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:09:09 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/04 17:05:54 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execution *creat_node()
{
    t_execution *exec;

    exec = gar_coll(sizeof(t_execution), 'a', 1);
	exec->cmd = NULL;
	exec->in_file = 0;
	exec->out_file = 1;
    exec->next = NULL;
    return(exec);
}

void add_node_to_list(t_execution **exec,t_execution *node)
{
    t_execution *tmp;

    if(!*exec)
    {
        *exec = node;
        return;
    }
    tmp = *exec;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void append_to_cmd(char *exp,t_execution *exec)
{
    int i;
    char **new_cmd;
    int j;
    
    if (!exp || !exec)
        return;
    i = 0;
    if(exec->cmd)
    {
        while(exec->cmd[i])
            i++;
    }
    new_cmd = gar_coll(sizeof(char *)*(i + 2),'a',1);
    j = 0;
    if(exec->cmd)
    {
        while(j < i)
        {
            new_cmd[j] = exec->cmd[j];
            j++;
        }
    }
    new_cmd[j] = ft_strdup(exp);
    new_cmd[j + 1] = NULL;
    exec->cmd = new_cmd;
}

int is_redirection(char *s)
{
    if(!ft_strcmp(s,"<") || !ft_strcmp(s,">") || !ft_strcmp(s,"<<") || !ft_strcmp(s,">>"))
        return(1);
    else
        return(0);
}


void split_cmd(t_tokenn *token)
{
    t_tokenn *tmp;
    t_execution *exec;
    t_execution *exec_list;
    
    tmp = token;
    exec_list = NULL;
    
    while(tmp)
    {
        exec = creat_node();
        while(tmp->type != PIPE)
        {
            if(tmp->type == EXP)
            {
                append_to_cmd(tmp->value,exec);
            }
            
            else if(is_redirection(tmp->value))
            {
                //handel redirections here function(tmp->next->value,exec)
                tmp = tmp->next->next;
            }
            tmp = tmp->next;
        }
        add_node_to_list(&exec_list,exec);
        if(tmp && tmp->type == PIPE)
            tmp = tmp->next;
    }
}