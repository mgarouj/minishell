/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:37:36 by mgarouj           #+#    #+#             */
/*   Updated: 2025/07/02 15:15:51 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_env(char *arg)
{
	write(2, "env: ", 5);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
}

int	check_argument(char *env)
{
	if (!ft_strcmp(env, "env") || !ft_strcmp(env, "ENV"))
		return (1);
	return (0);
}

int	ft_env(char **arg, t_env **env)
{
	t_env	*tmp;
	int		i;

	tmp = *env;
	if (!get_env_value("PATH", *env))
		return (print_err("env: No such file or directory"), 127);
	i = 0;
	while (arg[i])
	{
		if (!check_argument(arg[i]))
			return (print_error_env(arg[1]), 127);
		i++;
	}
	while (tmp)
	{
		if (!tmp->value)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_3putstr(tmp->key, "=", tmp->value, "\n");
		tmp = tmp->next;
	}
	return (0);
}
