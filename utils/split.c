/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:30:31 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/22 16:04:32 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

static int word_count(char *s)
{
    int count = 0;

    while (*s)
    {
        while (*s && is_whitespace(*s))
            s++;
        if (*s)
            count++;
        while (*s && !is_whitespace(*s))
            s++;
    }
    return (count);
}

static char *word_dup(char *start, int len)
{
    char *word = gar_coll(len + 1,'a');
    int i;
    
    i = 0;
    while (i < len)
    {
        word[i] = start[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

char **ft_split_whitespace(char *s)
{
    char **result;
    int i = 0;
    int len;
    
    if (!s)
        return (NULL);
    result = gar_coll(sizeof(char *) * (word_count(s) + 1),'a');
    if (!result)
        return (NULL);
    while (*s)
    {
        while (*s && is_whitespace(*s))
            s++;
        if (*s)
        {
            len = 0;
            while (s[len] && !is_whitespace(s[len]))
                len++;
            result[i++] = word_dup(s, len);
            s += len;
        }
    }
    result[i] = NULL;
    return (result);
}
