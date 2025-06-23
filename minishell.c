/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 21:43:56 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_exitval = NULL;

void	exit_minishell(int exit_s)
{
	gar_coll(0, 'f');
	fd_collec(0, 0);
	exit(exit_s);
}

void	leak(void)
{
	system("leaks minishell");
}

void	add_pwd_shlvl(t_env **l)
{
	export_in_env(l, "PWD", getcwd(NULL, 0),1);
	printf("env = %s\n", (*l)->value);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*trim;
	int			i;
	t_env		*l;
	t_tokenn	*token;
	t_execution	*exec_list;

	(void)ac;
	(void)av;
	handle_in();
	l = NULL;
	token = NULL;
	i = 0;
	while (env[i])
	{
		handel_env(env[i], &l);
		i++;
	}
	shelvl_path_underscore(&l);
	while (1)
	{
		g_env_exitval = l;
		signal_handler(1, l);
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		print_main(l,line);
		signal(SIGINT, SIG_IGN);
		if (line[0] != '\0')
		{
			add_history(line);
			trim = ft_strtrim(line, ft_strlen(line));
			free(line);
			if (!trim || trim[0] == '\0')
				continue ;
			if (!parssing(trim))
			{
				l->exit_status = 2;
				continue ;
			}
			token = tokenize(trim);
			if (!expand_rm_quotes(token, l))
				continue ;
			exec_list = NULL;
			if (!split_cmd(token, &exec_list, l))
				continue ;
			execute_cmd(&exec_list, &l);
		}
		else
			free(line);
	}
	return (0);
}
