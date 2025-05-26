/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:37:36 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/23 15:37:58 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_env(char *arg)
{
	write(2, "env: ", 5);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
}

int	ft_env(char **arg, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!get_env_value("PATH", *env))
	{
		write(2, "minishell: env: No such file or directory\n", 43);
		return (127);
	}
	if (arg[1])
	{
		print_error_env(arg[1]);
		return (127);
	}
	while (tmp)
	{
		ft_3putstr(tmp->key, "=", tmp->value, "\n");
		tmp = tmp->next;
	}
	return (0);
}
