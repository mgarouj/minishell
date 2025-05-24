/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:56:38 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/23 19:01:40 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
 

t_tokenn *create_token(enum token type, char *value)
{
    t_tokenn *new;

    new = gar_coll(sizeof(t_tokenn), 'a');
    if (!new)
        return (NULL);
    new->type = type;
    new->value = value;
    new->next = NULL;
    return (new);
}

void add_token(t_tokenn **head, t_tokenn *new_token)
{
    t_tokenn *temp;

    if (!*head)
    {
        *head = new_token;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_token;
}

int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void  handle_operator(char *line, int *i, t_tokenn **tokens)
{
    int start;
    enum token type;

    start = *i;
    if (line[*i] == '|')
    {
        type = PIPE;
        add_token(tokens, create_token(type,"|"));
        (*i)++;
        return;
    }
    else if (line[*i] == '<' && line[*i + 1] == '<')
    {
        type = HEREDOC;
        add_token(tokens, create_token(type,"<<"));
        (*i) += 2;
        return;
    }
    else if(line[*i] == '<')
    {   
        type = REDIRECTION_IN;
        add_token(tokens, create_token(type,"<"));
        (*i)++;
        return;
    }
    else if (line[*i] == '>' && line[*i + 1] == '>')
    {
        type = REDIRECTION_AP;
        add_token(tokens, create_token(type,">>"));
        (*i) += 2;
        return;
    }
    else
    {
        type = REDIRECTION_OUT;
        add_token(tokens, create_token(type,">"));
        (*i)++;
        return;
    }    
}

void handle_exp(char *line, int *i, t_tokenn **tokens)
{
	int start;

	while (line[*i] && !is_operator(line[*i]))
	{
		while (line[*i] == ' ' || line[*i] == '\t')
			(*i)++;

		start = *i;

		while (line[*i] && !is_operator(line[*i]) &&
			line[*i] != ' ' && line[*i] != '\t')
		{
			if (line[*i] == '"' || line[*i] == '\'')
			{
				char quote = line[*i];
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
			add_token(tokens, create_token(EXP, ft_strndup(&line[start], *i - start)));
	}
}

t_tokenn *tokenize(char *line)
{
    t_tokenn *tokens = NULL;
    int i = 0;

    while (line[i])
    {
        if (is_operator(line[i]))
            handle_operator(line, &i, &tokens);
        else if(!is_operator(line[i]) && line[i] != ' ' && line[i] != '\t')
            handle_exp(line, &i, &tokens);
        else
            i++;
    }
    return (tokens);
}

