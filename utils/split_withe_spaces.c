/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_withe_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:10:00 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/21 21:26:10 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	word_count(char *s)
{
	int	count;

	count = 0;
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

static char	*word_dup(char *start, int len)
{
	char	*word;
	int		i;

	word = gar_coll(len + 1, 'a');
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_whitespace(char *s)
{
	char	**result;
	int		i;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	result = gar_coll(sizeof(char *) * (word_count(s) + 1), 'a');
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

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}
