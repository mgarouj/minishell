/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:56:38 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/19 15:49:38 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
 

t_tokenn *create_token(enum token type, char *value)
{
    t_tokenn *new;

    new = gar_coll(sizeof(t_tokenn), 0, true);
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
    
    // add_token(tokens, create_token(type, ft_strndup(&line[start], *i - start + 1)));
    
    // (*i)++;
    // while(line[*i] == ' ' || line[*i] == '\t')
    //     (*i)++;
        
}

void handle_quotes(char *line, int *i, t_tokenn **tokens)
{
    int start;
    char quote_type;

    start = *i;
    quote_type = line[*i];
    (*i)++;
    while (line[*i] && line[*i] != quote_type)
        (*i)++;
    if (line[*i] == quote_type)
        (*i)++;
    if(quote_type == '\'')
        add_token(tokens,create_token(SINGLE_QUOTE,ft_strndup(&line[start], *i - start)));
    else if(quote_type == '"')
        add_token(tokens,create_token(DOUBLE_QUOTE,ft_strndup(&line[start], *i - start)));
}

void handle_exp(char *line, int *i, t_tokenn **tokens)
{
    int start;

    start = *i;
    // while (line[*i] && !is_operator(line[*i]) && line[*i] != '"' && line[*i] != '\'')
    //     (*i)++;
     while (line[*i] && !is_operator(line[*i]))
        (*i)++;
    add_token(tokens, create_token(EXP, ft_strndup(&line[start], *i - start)));
}

t_tokenn *tokenize(char *line)
{
    t_tokenn *tokens = NULL;
    int i = 0;

    while (line[i])
    {
        if (is_operator(line[i]))
            handle_operator(line, &i, &tokens);
        // else if (line[i] == '"' || line[i] == '\'')
        //     handle_quotes(line, &i, &tokens);
        else
            handle_exp(line, &i, &tokens);
    }
    return (tokens);
}

