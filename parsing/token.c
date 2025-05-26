/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:56:38 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/26 20:18:47 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_redirections(char *line, int *i, t_tokenn **tokens)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, create_token(HEREDOC, "<<",0));
		*i += 2;
	}
	else if (line[*i] == '<')
	{
		add_token(tokens, create_token(REDIRECTION_IN, "<",0));
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, create_token(REDIRECTION_AP, ">>",0));
		*i += 2;
	}
	else
	{
		add_token(tokens, create_token(REDIRECTION_OUT, ">",0));
		(*i)++;
	}
}

void	handle_operator(char *line, int *i, t_tokenn **tokens)
{
	if (line[*i] == '|')
	{
		add_token(tokens, create_token(PIPE, "|",0));
		(*i)++;
	}
	else
		handle_redirections(line, i, tokens);
}

static void	token_exp(char *line, int *i, t_tokenn **tokens)
{
	int		start;
	char	quote;
	int	quotes;
	
	skip_whitespace(line, i);
	start = *i;
	quotes = 0;
	while (line[*i] && !is_operator(line[*i]) && line[*i] != ' '
		&& line[*i] != '\t')
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			quotes = 1;
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	if (*i > start)
		add_token(tokens, create_token(EXP, ft_strndup(&line[start], *i
					- start),quotes));
}

void	handle_exp(char *line, int *i, t_tokenn **tokens)
{
	while (line[*i] && !is_operator(line[*i]))
		token_exp(line, i, tokens);
}

t_tokenn	*tokenize(char *line)
{
	t_tokenn	*tokens;
	int			i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (is_operator(line[i]))
			handle_operator(line, &i, &tokens);
		else if (!is_operator(line[i]) && line[i] != ' ' && line[i] != '\t')
			handle_exp(line, &i, &tokens);
		else
			i++;
	}
	return (tokens);
}
