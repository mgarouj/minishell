/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:16:41 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/27 19:24:24 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_path(t_env **env_list)
{
	t_env	*env;
	char	*path;
	char	*default_path;

	env = *env_list;
	path = get_env_value("PATH", env);
	if (!path)
	{
		default_path = "/gcc/bin:/usr/local/bin:/usr/local/sbin:/usr/bin:"
			"/usr/sbin:/bin:/sbin:.";
		export_in_env(env_list, "PATH", default_path, 0);
	}
}

void	add_underscore(t_env **env_list)
{
	t_env	*env;
	char	*path;

	env = *env_list;
	path = get_env_value("_", env);
	if (!path)
		export_in_env(env_list, "_", "/usr/bin/env", 1);
}

void	add_pwd(t_env **env)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	path = get_env_value("PWD", *env);
	if (!path)
		export_in_env(env, "PWD", pwd, 1);
	free(pwd);
}

void	add_oldpwd(t_env **env)
{
	char	*path;

	path = get_env_value("OLDPWD", *env);
	if (!path)
		null_value(env, "OLDPWD");
}

void	shelvl_path_underscore(t_env **env_list)
{
	t_env	*tmp_env;
	char	*old_value;
	int		new_value;

	tmp_env = *env_list;
	new_value = 0;
	old_value = get_env_value("SHLVL", tmp_env);
	if (!old_value)
		export_in_env(env_list, "SHLVL", "0", 1);
	else
	{
		new_value = ft_atoi(old_value);
		if (new_value >= 999)
		{
			ft_putstr_fd("minishell: warning: ", 1);
			ft_putstr_fd("shell level (1000) too high, resetting to 1\n", 1);
			new_value = 0;
		}
		new_value++;
		export_in_env(env_list, "SHLVL", ft_itoa(new_value), 1);
	}
	(add_path(env_list), add_underscore(env_list));
	(add_pwd(env_list), add_oldpwd(env_list));
}
