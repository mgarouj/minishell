/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/03 13:34:33 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void)
{
	gar_coll(0, 'f', 0);
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
	t_execution *exec;
	t_execution *t;
	
	(void)ac;
	(void)av;
	l = NULL;
	token = NULL;
	i = 0;
	while (env[i])
	{
		handel_env(env[i], &l);
		i++;
	}
	while (1)
	{
		line = readline("prompt ");
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


			tmp = token;
			while (tmp)
			{
				printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
				tmp = tmp->next;
			}
			//remove quotes and expaind only if there is no heredoc before
			remove_quotes(token, l);
			printf("***************************\n");
			tmp = token;
			while (tmp)
			{
				printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
				tmp = tmp->next;
			}
			// exec = gar_coll(sizeof(t_execution),'a',1);
			// exec->in_file = 0;
			// exec->out_file = 1;
			
	
			// if(!heredoc(token,exec))
			// 	continue;
			// // i have to split the cmd and make the execution linked list 
			
			// if(!handel_red(token,exec))
			// 	continue;
			
			// 	tmp = token;
			// while (tmp)
			// {
			// 	printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
			// 	tmp = tmp->next;
			// }
			
			// // execution 
			// // executionFunction (linkedlisgt, env)
			
		}
		else
			free(line);
	}
	return (0);
}
