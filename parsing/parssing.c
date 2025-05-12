/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:14:58 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/12 16:06:54 by fbelkass         ###   ########.fr       */
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
//validate
int	validate_redirection(char *line, int *i)
{
	char	redir;
	int		count;
	char	*param;

	redir = line[*i];
	count = 1;
	param = "|><";
	while (line[*i + count] == redir && count < 3)
		count++;
	if (redir == '>' && count > 2)
	{
		print_err("syntax error near unexpected token >");
		return (0);
	}
	else if (redir == '<' && count > 2)
	{
		print_err("syntax error near unexpected token <");
		return (0);
	}
	*i += count;
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

// int	parss_quote(char *line, int *i)
// {
// 	if (line[*i] == '"')
// 	{
// 		if (!find_dquote(line, i))
// 		{
// 			print_err("syntax error missing quote");
// 			return (0);
// 		}
// 	}
// 	else if (line[*i] == '\'')
// 	{
// 		if (!find_squote(line, i))
// 		{
// 			print_err("syntax error missing quote");
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// int	parssing(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (!parss_quote(line, &i))
// 			return (0);
// 		else if (line[i] == '<' || line[i] == '>')
// 		{
// 			if (!validate_redirection(line, &i))
// 				return (0);
// 		}
// 		else if (line[i] == '|')
// 		{
// 			if (!parss_pipe(line, &i))
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int parss_quote(char *line, int *i)
{
    char quote = line[*i];
    int start = *i;
    
    (*i)++; // move past the opening quote
    while (line[*i] && line[*i] != quote)
        (*i)++;
    
    if (!line[*i]) {  // reached end of string without closing quote
        *i = start;   // reset to opening quote position
        print_err("syntax error missing quote");
        return (0);
    }
    
    (*i)++; // move past the closing quote
    return (1);
}

int parssing(char *line)
{
    int i = 0;
    
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!parss_quote(line, &i))
                return (0);
            continue;
        }
        else if (line[i] == '<' || line[i] == '>')
        {
            if (!validate_redirection(line, &i))
                return (0);
            continue;
        }
        else if (line[i] == '|')
        {
            if (!parss_pipe(line, &i))
                return (0);
			continue;
        }
        i++;
    }
    return (1);
}