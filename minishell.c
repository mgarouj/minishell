/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/31 17:15:18 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void)
{
	gar_coll(0, 'f');
	fd_collec(0,0);
	exit(0);
}

void leak(void){
	system("leaks minishell");
}

// void test_mini()
void	add_pwd_shlvl(t_env **l)
{
	export_in_env(l, "PWD", getcwd(NULL, 0));
	printf("env = %s\n", (*l)->value);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*trim;
	int			i;
	t_env		*l;
	t_tokenn	*token;
	t_tokenn	*tmp;
	// atexit(leak);
	
	t_execution *exec_list;
	(void)ac;
	(void)av;
	// if env == NULL
	handle_in();
	l = NULL;
	token = NULL;
	i = 0;
	
	// if (!env && !env[0])
		// add_pwd_shlvl(&l);
	// signal_handler(1);
	while (env[i])
	{
		handel_env(env[i], &l);
		i++;
	}
	shelvl_path_underscore(&l);

	
	// l = env_to_list(env);
	
	while (1)
	{
		signal_handler(1);
		
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!line)
		{
			print_err("exit");
			exit_minishell();
		}
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
			
			//remove quotes and expaind only if there is no heredoc before
			if(!expand_rm_quotes(token, l))
				continue;
			tmp = token;
			while (tmp)
			{
				printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
				tmp = tmp->next;
			}
			
			printf("***************************\n");
			exec_list = NULL;
			if(!split_cmd(token,&exec_list,l))
				continue;
			t_execution *t = exec_list;
			int i;
				
				while (t)
				{
					printf("Command:\n");
					i = 0;
					if (t->cmd)
					{
						while (t->cmd[i])
						{
							printf("  [%d]: %s\n", i, t->cmd[i]);
							i++;
						}
					}
					else
						printf("no command\n");
					printf("  [%d]: in_file = %d\n", i, t->in_file);
					printf("  [%d]: out_file = %d\n", i, t->out_file);
						
					
					t = t->next;
				}
			
			// // execution 
			printf("\n\n*********************\n");
			execute_cmd(&exec_list, &l);
			// printf("exit status = %d \n", l->exit_status);
		}
		else
			free(line);
	}

	// gcc parsing/*.c utils/*.c env_list/*.c libft_fonction/*.c exc/*.c built/*.c minishell.c -lreadline
	return (0);
}
