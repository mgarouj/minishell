/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retoken.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:18:54 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/21 21:23:39 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




void retoken(t_tokenn *token)
{
    t_tokenn *tmp;
    
    tmp = token;
    while(tmp)
    {
        if(tmp->type==EXP && (ft_strchr(tmp->value,' ') || ft_strchr(tmp->value,'\t')))
            //split that token and add that node
    }
}