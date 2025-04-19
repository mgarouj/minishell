/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:47:31 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/19 15:46:27 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


t_env *create_env(char *key, char *value)
{
    t_env *new;

    new = gar_coll(sizeof(t_env), 0, true);
    if (!new)
        return (NULL);
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}

void add_env(t_env **head, t_env *new_env)
{
    t_env *temp;

    if (!*head)
    {
        *head = new_env;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_env;
}



void handel_env(char *s,t_env **env)
{
    char **l;

    l = ft_split(s,'='),

    add_env(env,create_env(l[0],l[1]));

}

// #include <stdio.h>

// void print_env(t_env *l)
// {
//     t_env *tmp;
//     tmp = l;

//     while (tmp)
//     {
//         printf("%s=%s\n",tmp->key,tmp->value);
//         tmp = tmp -> next;
//     }
    
// }

// int main(int ac, char **av, char **env)
// {
//     t_env *l = NULL;
//     int i = 0;
//     while (env[i])
//     {
//         handel_env(env[i], &l);
//         i++;
//     }

//     print_env(l);
// }
