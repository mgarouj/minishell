/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:25:28 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/24 14:30:37 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	find_dquote(char *line, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '"')
			return (1);
		(*i)++;
	}
	return (0);
}

int	find_squote(char *line, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '\'')
			return (1);
		(*i)++;
	}
	return (0);
}

int	is_valid_redir_count(char *line, int *i, char redir)
{
	int	count;

	count = 1;
	while (line[*i + count] == redir && count < 3)
		count++;
	if ((redir == '>' || redir == '<') && count > 2)
	{
		if (redir == '>')
			print_err("syntax error near unexpected token >");
		else
			print_err("syntax error near unexpected token <");
		return (0);
	}
	*i += count;
	return (1);
}

int	is_valid_redir_target(char *line, int *i)
{
	char	*param;

	param = "|><";
	while (is_whitespace(line[*i]))
		(*i)++;
	if (line[*i] == '\0')
	{
		print_err("syntax error near unexpected token 'newline'");
		return (0);
	}
	if (ft_strchr(param, line[*i]))
	{
		if (line[*i] == '|')
			print_err("syntax error near unexpected token |");
		else if (line[*i] == '>')
			print_err("syntax error near unexpected token >");
		else if (line[*i] == '<')
			print_err("syntax error near unexpected token <");
		return (0);
	}
	return (1);
}
