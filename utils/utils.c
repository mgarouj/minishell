/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:03 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/29 19:05:51 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*dup;

	dup = gar_coll(n + 1, 'a');
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*sub_str(char *s, int size)
{
	int		i;
	char	*r;

	r = gar_coll(size + 1, 'a');
	if (!r)
		return (NULL);
	i = 0;
	while (i < size)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_strdup(char *s)
{
	int		l;
	int		i;
	char	*r;

	i = 0;
	l = ft_strlen(s);
	r = gar_coll((l + 1) * sizeof(char), 'a');
	if (!r)
		return (NULL);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*r;
	int		i;
	int		slen;

	if (!s)
		return (NULL);
	if ((int)start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s) - (int)start < len)
		slen = ft_strlen(s) - (int)start;
	else
		slen = len;
	r = (char *)gar_coll((slen + 1) * sizeof(char), 'a');
	if (!r)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
