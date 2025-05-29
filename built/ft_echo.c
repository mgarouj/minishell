/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:36:05 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/28 15:50:40 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_flag(char *flag)
{
	int	i;

	i = 0;
	if (!flag || flag[i] != '-')
		return (false);
	i++;
	if (!flag[i])
		return (false);
	while (flag[i])
	{
		if (flag[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

void	print_args(char **args, bool n_flag)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(char **args)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (!args[i])
		return (ft_putstr_fd("\n", 1), 0);
	while (check_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	print_args(args + i, n_flag);
	return (0);
}
