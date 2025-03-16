/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:28:12 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/16 17:11:55 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"


t_tokenn *new_token(enum token type, char *value)
{
    t_tokenn *token = malloc(sizeof(t_tokenn));
    if (!token)
        return NULL;
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

void add_token(t_tokenn **list, enum token type, char *value)
{
    t_tokenn *new = new_token(type, value);
    if (!new)
        return;
    if (!*list)
        *list = new;
    else
    {
        t_tokenn *temp = *list;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}


t_tokenn ** tokenize(char *line)
{
    int i;
    t_tokenn ** r;
    
    i = 0;
    while(line[i])
    {
        
    }
}