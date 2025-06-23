/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:11:53 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 21:41:57 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_main(t_env *env_list, char *line)
{
    if (!line)
    {
        print_err("exit");
        set_exit_status(&env_list, env_list->exit_status);
        exit_minishell(env_list->exit_status);
    }
}
t_env	*init_env_list(char **env)
{
	t_env	*l;
	int		i;

	l = NULL;
	i = 0;
	while (env[i])
	{
		handel_env(env[i], &l);
		i++;
	}
	shelvl_path_underscore(&l);
	return (l);
}
void	read_and_execute(char *line, t_env *l, char *trim)
{
	t_tokenn	*token;
	t_execution	*exec_list;

	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	add_history(line);
	trim = ft_strtrim(line, ft_strlen(line));
	free(line);
	if (!trim || trim[0] == '\0')
		return ;
	if (!parssing(trim))
	{
		l->exit_status = 2;
		return ;
	}
	token = tokenize(trim);
	if (!expand_rm_quotes(token, l))
		return ;
	exec_list = NULL;
	if (!split_cmd(token, &exec_list, l))
		return ;
	execute_cmd(&exec_list, &l);
}

void	exit_minishell(int exit_s)
{
	gar_coll(0, 'f');
	fd_collec(0, 0);
	exit(exit_s);
}

void	main_loop(t_env *l)
{
	char	*line;
    char		*trim;

    trim = NULL;
	while (1)
	{
		g_env_exitval = l;
		signal_handler(1, l);
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		print_main(l, line);
		signal(SIGINT, SIG_IGN);
		read_and_execute(line, l, trim);
	}
}
