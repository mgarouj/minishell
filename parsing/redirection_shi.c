/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_shi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:00 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/20 21:38:03 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"






void handel_red(t_tokenn *token,t_execution *exec)
{
    t_tokenn *tmp;
    
    tmp = token;
    while (tmp)
    {
        if(tmp->type == REDIRECTION_IN ||
            tmp->type == REDIRECTION_OUT ||
            tmp->type == REDIRECTION_AP)
        {
            if (!tmp->next || tmp->next->type != EXP)
            {
                //handel syntx error!
            }
            if(tmp->type == REDIRECTION_IN)
                //handel_it
            else if(tmp->type == REDIRECTION_OUT)
                //HANDEL_IT
            else if(tmp->type == REDIRECTION_AP)
                //HANDEL_IT
        }
        else
            tmp = tmp->next;
    }
    
}