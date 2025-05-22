/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retoken.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:18:54 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/22 13:16:03 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *normalize_spaces(char *str)
{
	int i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	return (str);
}


void split_and_insert_tokens(t_tokenn **current)
{
	t_tokenn *next;
	t_tokenn *last;
	char **words;
	int i;

	if (!current || !*current)
		return;

	normalize_spaces((*current)->value); // converts tabs to spaces if needed
	words = ft_split((*current)->value, ' ');
	if (!words || !words[0])
		return;

	// Save next pointer and free old value
	next = (*current)->next;
	free((*current)->value);
	(*current)->value = ft_strdup(words[0]);
	last = *current;

	// Create and chain new tokens for remaining words
	i = 1;
	while (words[i])
	{
		t_tokenn *new = create_token(EXP, ft_strdup(words[i]));
		if (!new)
			return; // handle memory errors properly
		last->next = new;
		last = new;
		i++;
	}
	last->next = next;
}


void retoken(t_tokenn *token)
{
	t_tokenn *tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == EXP && (ft_strchr(tmp->value, ' ') || ft_strchr(tmp->value, '\t')))
			split_and_insert_tokens(&tmp);
		tmp = tmp->next;
	}
}
