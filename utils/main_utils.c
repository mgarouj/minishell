/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:11:53 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/27 14:47:32 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(int exit_s)
{
	gar_coll(0, 'f');
	fd_collec(0, 0);
	exit(exit_s);
}

void	add_pwd_shlvl(t_env **l)
{
	export_in_env(l, "PWD", getcwd(NULL, 0), 1);
	printf("env = %s\n", (*l)->value);
}

int	handle_eof(char *line, t_env *env)
{
	if (!line)
	{
		print_err("exit");
		set_exit_status(1, env->exit_status);
		exit_minishell(env->exit_status);
		return (0);
	}
	return (1);
}

t_env	*init_env(char **env)
{
	t_env	*list;
	int		i;

	list = NULL;
	i = 0;
	while (env[i])
		handel_env(env[i++], &list);
	return (list);
}
