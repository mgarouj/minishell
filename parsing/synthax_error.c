/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:14:58 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/24 15:04:57 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_redirection(char *line, int *i)
{
	char	redir;

	redir = line[*i];
	if (!is_valid_redir_count(line, i, redir))
		return (0);
	if (!is_valid_redir_target(line, i))
		return (0);
	return (1);
}

int	parss_pipe(char *line, int *i)
{
	if ((*i) == 0 || line[(*i) + 1] == '\0')
	{
		print_err("syntax error near unexpected token `|'");
		return (0);
	}
	if (line[(*i) + 1] == '|')
	{
		print_err("syntax error near unexpected token `|'");
		return (0);
	}
	(*i)++;
	while (is_whitespace(line[*i]))
		(*i)++;
	if (line[*i] == '\0' || line[*i] == '|')
	{
		print_err("syntax error near unexpected token `|'");
		return (0);
	}
	return (1);
}

int	parss_quote(char *line, int *i)
{
	char	quote;
	int		start;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		*i = start;
		print_err("syntax error missing quote");
		return (0);
	}
	(*i)++;
	return (1);
}

int	handle_parsing_case(char *line, int *i)
{
	if (line[*i] == '\'' || line[*i] == '"')
	{
		if (!parss_quote(line, i))
			return (0);
		return (2);
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		if (!validate_redirection(line, i))
			return (0);
		return (2);
	}
	else if (line[*i] == '|')
	{
		if (!parss_pipe(line, i))
			return (0);
		return (2);
	}
	return (1);
}

int	parssing(char *line)
{
	int	i;
	int	status;

	i = 0;
	while (line[i])
	{
		status = handle_parsing_case(line, &i);
		if (status == 0)
			return (0);
		else if (status == 2)
			continue ;
		i++;
	}
	return (1);
}
