/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:09:09 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/02 20:59:52 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void append_to_cmd(char *exp,t_execution *exec)
{
    
}

int is_redirection(char *s)
{
    if(!ft_strcmp(s,"<") || !ft_strcmp(s,">") || !ft_strcmp(s,"<<") || !ft_strcmp(s,">>"))
        return(1);
    else
        return(0);
}

void handel_cmd(char *exp,char **cmd)
{
    int i;
    int start;
    int j;
    
    i = 0;
    j = 0;
    while (exp[i])
    {
        if(exp[i] == '$')
            //expaind
        i++;
    }
    i = 0;
    while(exp[i])
    {
        while(exp[i] == ' ' || exp[i] == '\t')
            i++;
        start = i;
        while(exp[i] && exp[i] != ' ' && exp[i] != '\t')
            i++;
        cmd[j++] = ft_strndup(exp + start,i - start);
    }
    cmd[j] = NULL;
}


void split_cmd(t_tokenn *token)
{
    t_tokenn *tmp;
    t_execution *exec;
    
    tmp = token;
    
    exec = gar_coll(sizeof(t_execution),'a',1);
    
    while(tmp)
    {
        while(tmp->type != PIPE)
        {
            if(tmp->type == EXP)
            {
                
            }
            else if(is_redirection(tmp->value))
                
        }
        
    }
}