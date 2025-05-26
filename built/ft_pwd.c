/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:38:58 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/26 10:18:10 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_env **env)
{
	char	*cwd;
	int		free_flag;

	free_flag = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = get_env_value("PWD", *env);
		if (cwd)
			ft_3putstr(cwd, "\n", NULL, NULL);
		else
		{
			cwd = (*env)->pwd;
			if (cwd)
				ft_3putstr(cwd, "\n", NULL, NULL);
		}
	}
	else
	{
		ft_3putstr(cwd, "\n", NULL, NULL);
		free_flag = 1;
	}
	if (free_flag)
		free(cwd);
	return (0);
}
