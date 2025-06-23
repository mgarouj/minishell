/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:48:33 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 15:36:07 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenn	*create_token(enum e_token type, char *value, int quotes)
{
	t_tokenn	*new;

	new = gar_coll(sizeof(t_tokenn), 'a');
	if (!new)
		return (NULL);
	new->type = type;
	new->quotes = quotes;
	new->expan_toex = 0;
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

void	skip_quotes(const char *line, int *i, char quote)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
}
