/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:36:31 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/21 21:13:15 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_redin(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdin") == 0)
		exec->in_file = STDIN_FILENO;
	else
	{
		fd = open(filename, O_RDONLY);
		fd_collec(fd, 1);
		if (fd == -1)
		{
			fd_collec(0, 0);
			return (0);
		}
		if (exec->in_file != 0)
			close(exec->in_file);
		exec->in_file = fd;
	}
	return (1);
}

int	handel_reout(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdout") == 0)
		exec->out_file = STDOUT_FILENO;
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd_collec(fd, 1);
		if (fd == -1)
		{
			fd_collec(0, 0);
			return (0);
		}
		if (exec->out_file != 1)
			close(exec->out_file);
		exec->out_file = fd;
	}
	return (1);
}

int	handel_redappend(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdout") == 0)
		exec->out_file = STDOUT_FILENO;
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		fd_collec(fd, 1);
		if (fd == -1)
		{
			print_err("failed to open file for append");
			fd_collec(0, 0);
			return (0);
		}
		if (exec->out_file != 1)
			close(exec->out_file);
		exec->out_file = fd;
	}
	return (1);
}
