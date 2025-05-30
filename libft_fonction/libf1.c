/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libf1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:55:56 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/30 17:28:10 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	i;
	int	j;

	i = 0;
	if (haystack == NULL && needle != NULL && len == 0)
		return (NULL);
	if (!needle[0])
		return ((char *)(haystack));
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_3(char *s1, char *s2)
{
	char	*join3;
	int		i;
	int		j;

	if (!s2)
		return (ft_strdup(s1));
	join3 = gar_coll(ft_strlen(s1) + ft_strlen(s2) + 2, 'a');
	i = 0;
	while (s1[i])
	{
		join3[i] = s1[i];
		i++;
	}
	join3[i++] = '=';
	j = 0;
	while (s2[j])
	{
		join3[i] = s2[j];
		j++;
		i++;
	}
	join3[i] = '\0';
	return (join3);
}