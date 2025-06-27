/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:38:10 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/27 12:06:27 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_minishell(int exit_value)
{
	gar_coll(0, 'f');
	fd_collec(0, 0);
	exit(exit_value);
}

void	exit_error(char *s2, int f)
{
	if (f == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (f == 2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		if (s2)
			ft_putstr_fd(s2, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

int	ft_exit(char **arg, int exit_status)
{
	int	i;

	i = 0;
	if (isatty(0) && isatty(1) && isatty(2))
		ft_putstr_fd("exit\n", 1);
	if (arg[0] && arg[1] && arg[2])
		return (exit_error(NULL, 1), 1);
	if (arg[1])
	{
		if (arg[1][0] == '-' || arg[1][0] == '+')
			i++;
		while (arg[i])
		{
			if (ft_isalpha(arg[1][i]))
				(exit_error(arg[1], 2), ft_exit_minishell(2));
			i++;
		}
		ft_exit_minishell(ft_atoi(arg[1]) % 256);
	}
	gar_coll(0, 'f');
	fd_collec(0, 0);
	exit(exit_status);
}
