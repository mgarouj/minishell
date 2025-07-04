/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:30 by mgarouj           #+#    #+#             */
/*   Updated: 2025/07/04 16:41:48 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(const char *msg)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(msg);
		return (-1);
	}
	return (pid);
}

void	clean_all_and_exit(void)
{
	gar_coll(0, 1);
	fd_collec(0, 0);
	exit(EXIT_FAILURE);
}

void	init_pipe_or_exit(t_execution *cmd, int prev_read)
{
	if (cmd->is_last == false)
	{
		if (pipe(cmd->pipe_fd) == -1)
		{
			perror("pipe");
			close_safe(prev_read);
			clean_all_and_exit();
		}
	}
}

pid_t	try_fork_or_exit(t_execution *cmd, int prev_read)
{
	pid_t	pid;

	pid = ft_fork("fork in pipe");
	if (pid == -1)
	{
		close_safe(prev_read);
		if (cmd->is_last == false)
		{
			close_safe(cmd->pipe_fd[0]);
			close_safe(cmd->pipe_fd[1]);
		}
		clean_all_and_exit();
	}
	return (pid);
}

void	close_safe(int fd)
{
	if (fd >= 0)
		close(fd);
}
