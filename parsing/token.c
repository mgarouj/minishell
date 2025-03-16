/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:56:38 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/16 20:44:21 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

t_tokenn *create_token(enum token type, char *value)
{
    t_tokenn *new;

    new = malloc(sizeof(t_tokenn));
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

int handle_operator(char *line, int *i, t_tokenn **tokens)
{
    int start;
    enum token type;

    start = *i;
    if (line[*i] == '|')
        type = PIPE;
    else if (line[*i] == '<' && line[*i + 1] == '<')
    {
        type = HEREDOC;
        (*i)++;
    }
    else if (line[*i] == '<')
        type = REDIRECTION_IN;
    else if (line[*i] == '>' && line[*i + 1] == '>')
    {
        type = REDIRECTION_OUT;
        (*i)++;
    }
    else
        return (0);
    add_token(tokens, create_token(type, strndup(&line[start], *i - start + 1)));
    return (1);
}

int handle_quotes(char *line, int *i, t_tokenn **tokens)
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
    add_token(tokens, create_token(
        (quote_type == '\'') ? SINGLE_QUOTE : DOUBLE_QUOTE,
        strndup(&line[start], *i - start)
    ));
    return (1);
}

int handle_word(char *line, int *i, t_tokenn **tokens)
{
    int start;

    start = *i;
    while (line[*i] && !is_operator(line[*i]) && line[*i] != ' ' && line[*i] != '\t')
        (*i)++;
    add_token(tokens, create_token(EXP, strndup(&line[start], *i - start)));
    return (1);
}

t_tokenn *tokenize(char *line)
{
    t_tokenn *tokens;
    int i;

    tokens = NULL;
    i = 0;
    while (line[i])
    {
        else if (is_operator(line[i]))
            handle_operator(line, &i, &tokens);
        else if (line[i] == '"' || line[i] == '\'')
            handle_quotes(line, &i, &tokens);
        else
            handle_word(line, &i, &tokens);
    }
    return (tokens);
}
