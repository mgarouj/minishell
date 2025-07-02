/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/02 12:35:13 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_in_readline = 0;

void	process_line(char *line, t_tokenn **token, t_execution **exec_list,
		t_env **env)
{
	char		*trim;

	add_history(line);
	trim = ft_strtrim(line, ft_strlen(line));
	free(line);
	if (!trim || trim[0] == '\0')
		return ;
	if (!parssing(trim))
	{
		set_exit_status(1, 2);
		return ;
	}
	*token = tokenize(trim);
	if (!expand_rm_quotes(*token, *env))
		return ;
	*exec_list = NULL;
	if (!split_cmd(*token, exec_list, *env))
		return ;
	execute_cmd(exec_list, env);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_env		*env_list;
	t_tokenn	*token;
	t_execution	*exec_list;

	env_list = init_env(env);
	(void)ac;
	(void)av;
	handle_in();
	shelvl_path_underscore(&env_list);
	signal_handler(1);
	while (1)
	{
		g_in_readline = 1;
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		g_in_readline = 0;
		if (!handle_eof(line))
			break ;
		if (line[0])
			process_line(line, &token, &exec_list, &env_list);
		else
			free(line);
		fd_collec(0, 0);
	}
	return (0);
}
