/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporttttt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:32:22 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/22 17:22:12 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	normal_export(t_env **env, char *arg)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] && !(arg[i] == '='))
		i++;
	if (!arg[i])
		return ;
	key = ft_substr(arg, 0, i);
	value = ft_strdup(arg + i + 1);
	export_in_env(env, key, value, 1);
}

void	export_plus_equal(t_env **env, char *arg, int i)
{
	char	*key;
	char	*value;
	char	*old_value;
	char	*new_value;
	t_env	*exist;

	while (arg[i] && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	key = ft_substr(arg, 0, i);
	value = ft_strdup(arg + i + 2);
	exist = find_var(*env, key);
	if (exist && exist->value)
	{
		old_value = exist->value;
		new_value = ft_strjoin(old_value, value);
		exist->value = new_value;
	}
	else
		export_in_env(env, key, value, 1);
}

int	handle_arg1(char *v)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (v[i] && v[i] != '=')
	{
		if (!ft_lnum_export(v[i]) && v[i + 1] != '=')
			flag++;
		i++;
	}
	i = 0;
	if (flag || v[0] == '=' || (v[0] >= '0' && v[0] <= '9'))
	{
		ft_3putstr("minishell: export: ", v, ": not a valid identifier\n",
			NULL);
		return (1);
	}
	return (0);
}
