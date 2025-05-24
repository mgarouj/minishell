/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:01 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/24 18:34:56 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_redin(char *filename, t_execution *exec)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	fd_collec(fd, 1);
	if (fd == -1)
	{
		print_err("failed to open input file");
		fd_collec(0, 0);
		return (0);
	}
	if (exec->in_file != 0)
		close(exec->in_file);
	exec->in_file = fd;
	return (1);
}

int	handel_reout(char *filename, t_execution *exec)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd_collec(fd, 1);
	if (fd == -1)
	{
		print_err("failed to open output file");
		fd_collec(0, 0);
		return (0);
	}
	if (exec->out_file != 1)
		close(exec->out_file);
	exec->out_file = fd;
	return (1);
}

int	handel_redappend(char *filename, t_execution *exec)
{
	int	fd;

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
	return (1);
}

int	process_heredoc_input(int pipe_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_err("heredoc input error");
			return (0);
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
	return (1);
}

int	handle_heredoc(char *delimiter, t_execution *exec)
{
	int	fd[2];

	if (!delimiter)
		return (0);
	if (pipe(fd) == -1)
	{
		print_err("heredoc error");
		return (0);
	}
	if (!process_heredoc_input(fd[1], delimiter))
	{
		close(fd[1]);
		close(fd[0]);
		return (0);
	}
	close(fd[1]);
	if (exec->in_file != 0)
		close(exec->in_file);
	exec->in_file = fd[0];
	return (1);
}
