/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:48:33 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/26 19:46:10 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenn	*create_token(enum e_token type, char *value,int quotes)
{
	t_tokenn	*new;

	new = gar_coll(sizeof(t_tokenn), 'a');
	if (!new)
		return (NULL);
	new->type = type;
	new->quotes = quotes;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_token(t_tokenn **head, t_tokenn *new_token)
{
	t_tokenn	*temp;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}
