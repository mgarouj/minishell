/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/16 20:08:32 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void)
{
	gar_coll(0, 'f');
	fd_collec(0,0);
	exit(0);
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
	// if env == NULL
	if (!env || !*env)
		return 1;


	
	l = NULL;
	token = NULL;
	i = 0;
	while (env[i])
	{
		handel_env(env[i], &l);
		i++;
	}
	
	// l = env_to_list(env);
	
	while (1)
	{
		// signal_handler();
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
			
			//remove quotes and expaind only if there is no heredoc before
			expand_rm_quotes(token, l);
			tmp = token;
			// while (tmp)
			// {
			// 	printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
			// 	tmp = tmp->next;
			// }
			
			// printf("***************************\n");
			exec_list = NULL;
			if(!split_cmd(token,&exec_list))
				continue;
			// t_execution *t = exec_list;
			// int i;
				
			// 	while (t)
			// 	{
			// 		printf("Command:\n");
			// 		i = 0;
			// 		if (t->cmd)
			// 		{
			// 			while (t->cmd[i])
			// 			{
			// 				printf("  [%d]: %s\n", i, t->cmd[i]);
			// 				i++;
			// 			}
			// 		}
			// 		else
			// 			printf("no command\n");
			// 		printf("  [%d]: in_file = %d\n", i, t->in_file);
			// 		printf("  [%d]: out_file = %d\n", i, t->out_file);
						
					
			// 		t = t->next;
			// 	}
			
			
			// execution 
			execute_cmd(&exec_list, &l);
			// printf("exit status = %d \n", l->exit_status);
		}
		else
			free(line);
	}
	return (0);
}
