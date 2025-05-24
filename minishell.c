/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/24 19:10:29 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void)
{
	gar_coll(0, 'f');
	fd_collec(0,0);
	exit(0);
}

void add_path(t_env **env_list)
{
	t_env *env;
	char *path;

	env = *env_list;
	path = get_env_value("PATH", env);
	if (!path)
		export_in_env(env_list, "PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
}

void add_underscore(t_env **env_list)
{
	t_env *env;
	char *path;

	env = *env_list;
	path = get_env_value("_", env);
	if (!path)
		export_in_env(env_list, "_",
				"/usr/bin/env");
}


void shelvl_path_underscore(t_env **env_list)
{
	t_env *tmp_env;
	char *old_value;
	int new_value;

	tmp_env = *env_list;
	old_value = get_env_value("SHLVL", tmp_env);
	if (!old_value)
		export_in_env(env_list, "SHLVL", "0");
	else
	{
		new_value = ft_atoi(old_value);
		if (new_value >= 999)
		{
			ft_putstr_fd("minishell: warning: shell level (1000) too high, resetting to 1\n", 1);
			new_value = 0;
		}
		new_value++;
		export_in_env(env_list, "SHLVL", ft_itoa(new_value));
	}
	add_path(env_list);
	add_underscore(env_list);
}

int check_expand(t_tokenn *token)
{
	t_tokenn *tmp;

	tmp = token;
	while(tmp)
	{
		if(tmp->type == EXP && ft_strchr(tmp->value,'$'))
			return(1);
		tmp = tmp->next;
	}
	return(0);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*trim;
	int			i;
	t_env		*l;
	t_tokenn	*token;
	t_tokenn	*tmp;
	
	t_execution *exec_list;
	
	(void)ac;
	(void)av;	
	l = NULL;
	token = NULL;
	i = 0;
	signal_handler();
	while (env[i])
	{
		handel_env(env[i], &l);
		i++;
	}

	shelvl_path_underscore(&l);	
	while (1)
	{
		line = readline("\001\033[1;32m\002minishell> \001\033[0m\002");
		if (!line)
		{
			print_err("exit");
			exit_minishell();
		}
		if (line[0] != '\0')
		{
			add_history(line);
			trim = ft_strtrim(line, ft_strlen(line));
			free(line);
			if (!trim || trim[0] == '\0')
				continue ;
			if (!parssing(trim))
				continue ;
			token = tokenize(trim);
			
			expand_rm_quotes(token, l);
			
			exec_list = NULL;
			if(!split_cmd(token,&exec_list))
				continue;
			execute_cmd(&exec_list, &l);
		}
		else
			free(line);
	}
	return (0);
}
