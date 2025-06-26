/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:11:53 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/24 13:15:42 by fbelkass         ###   ########.fr       */
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
		set_exit_status(&env, env->exit_status);
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
