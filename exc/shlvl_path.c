/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:16:41 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/29 19:33:04 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_path(t_env **env_list)
{
	t_env	*env;
	char	*path;

	env = *env_list;
	path = get_env_value("PATH", env);
	if (!path)
		export_in_env(env_list, "PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
}

void	add_underscore(t_env **env_list)
{
	t_env	*env;
	char	*path;

	env = *env_list;
	path = get_env_value("_", env);
	if (!path)
		export_in_env(env_list, "_",
			"/usr/bin/env");
}

void	add_pwd(t_env **env)
{
	char *pwd;
	// t_env *tmp_pwd;
	char *path;

	pwd = getcwd(NULL, 0);
	
	if (!pwd)
		return ;
	path = get_env_value("PWD", *env);
	if (!path)
		export_in_env(env, "PWD",pwd);
	free(pwd);
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
		export_in_env(env_list, "SHLVL", "0");
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
		export_in_env(env_list, "SHLVL", ft_itoa(new_value));
	}
	add_path(env_list);
	add_underscore(env_list);
	add_pwd(env_list);
}

void	handle_in(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("not running in interactive mode. Exiting...\n", 2);
		exit(1);
	}
}
