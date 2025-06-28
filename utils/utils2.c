/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:45:42 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/28 17:38:12 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strtrim(char *s, int size)
{
	int		start;
	int		end;
	char	*r;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && (s[start] == ' ' || s[start] == '\t'))
		start++;
	end = size - 1;
	while (end > start && (s[end] == ' ' || s[end] == '\t'))
		end--;
	r = sub_str(s + start, end - start + 1);
	if (!r)
		return (NULL);
	return (r);
}

int	count(char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

char	**copy(char *s, char c, char **r)
{
	int	i;
	int	start;
	int	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			r[l] = ft_substr(s, start, i - start);
			l++;
		}
	}
	r[l] = NULL;
	return (r);
}

char	**ft_split(char *s, char c)
{
	char	**r;

	if (!s)
		return (NULL);
	r = (char **)gar_coll((count(s, c) + 1) * sizeof(char *), 'a');
	if (!r)
		return (NULL);
	return (copy(s, c, r));
}
