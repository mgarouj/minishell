/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:14:12 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/30 18:55:47 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_cd(int f1, int f2, char *c1, char *c2)
{
	if (!f1)
		free(c1);
	if (!f2)
		free(c2);
	return (0);
}

int	change_directory(char *path, t_env *env)
{
	char	*cwd;
	char	*n_c;
	int		f2;
	int		f1;

	cwd = getcwd(NULL, 0);
	f1 = 0;
	f2 = 0;
	if (!cwd)
	{
		cwd = ft_strdup(env->pwd);
		f1 = 1;
	}
	change_env_value(&env, "OLDPWD", cwd);
	if (chdir(path) == -1)
		return (perror("minishell: cd"), 1);
	n_c = getcwd(NULL, 0);
	if (!n_c)
	{
		n_c = ft_strjoin(cwd, "/..");
		f2 = 1;
	}
	change_env_value(&env, "PWD", n_c);
	env->pwd = ft_strdup(n_c);
	return (free_cd(f1, f2, cwd, n_c));
}

int	ft_cd(char **arg, t_env *env)
{
	char	*path;

	if (!arg[1])
	{
		path = get_env_value("HOME", env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (1);
		}
	}
	else if (arg[1][0] == '\0') // يعني: cd ""
	{
		ft_putstr_fd("minishell: cd: : No such file or directory\n", 1);
		return (1);
	}
	else
		path = arg[1];
	if (path)
		return (change_directory(path, env));
	return (1);
}
