/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:55:56 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/02 15:16:17 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env(char *key, char *value)
{
	t_env	*new;

	new = gar_coll(sizeof(t_env), 'a');
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->exit_status = 0;
	new->next = NULL;
	return (new);
}

void	add_env(t_env **head, t_env *new_env)
{
	t_env	*temp;

	if (!*head)
	{
		*head = new_env;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
}

void	handel_env(char *s, t_env **env)
{
	char	**l;

	l = ft_split(s, '=');
	add_env(env, create_env(l[0], l[1]));
}
