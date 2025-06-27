/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:36:31 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/27 19:09:56 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_readable_input_file(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		print_err_ex(": No such file or directory", filename);
		return (0);
	}
	if (access(filename, R_OK) != 0)
	{
		print_err_ex(": Permission denied", filename);
		return (0);
	}
	return (1);
}

int	handel_redin(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdin") == 0)
	{
		exec->in_file = STDIN_FILENO;
		return (1);
	}
	if (!check_readable_input_file(filename))
		return (0);
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
	return (1);
}

void	assign_out_file(t_execution *exec, int fd)
{
	if (exec->out_file != STDOUT_FILENO)
		close(exec->out_file);
	exec->out_file = fd;
	fd_collec(fd, 1);
}

int	handel_reout(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdout") == 0)
	{
		if (exec->out_file != STDOUT_FILENO)
		{
			close(exec->out_file);
			exec->out_file = STDOUT_FILENO;
		}
		return (1);
	}
	if (!check_writable_file(filename))
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_err_ex(": Failed to open for write", filename);
		return (0);
	}
	assign_out_file(exec, fd);
	return (1);
}

int	handel_redappend(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdout") == 0)
	{
		if (exec->out_file != STDOUT_FILENO)
		{
			close(exec->out_file);
			exec->out_file = STDOUT_FILENO;
		}
		return (1);
	}
	if (!check_writable_file(filename))
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_err_ex(": Failed to open for append", filename);
		fd_collec(0, 0);
		return (0);
	}
	assign_out_file(exec, fd);
	return (1);
}
