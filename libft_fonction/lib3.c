/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:20:23 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/13 14:54:45 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	sign_spc(char *str, int *skip)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*skip = i;
	return (sign);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	o;

	i = 0;
	result = 0;
	sign = sign_spc((char *)str, &i);
	while (((char *)str)[i] >= '0' && ((char *)str)[i] <= '9')
	{
		o = result;
		result = result * 10 + (((char *)str)[i++] - 48);
		if ((result / 10) != o)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
	}
	return (result * sign);
}