/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libf1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:55:56 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/13 20:02:03 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	i;
	int	j;
	int	n_len;

	i = 0;
	n_len = ft_strlen(needle);
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
