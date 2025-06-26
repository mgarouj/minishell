/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:17:37 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/24 13:18:12 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_1(t_execution *exec, t_her *var_her)
{
	if (!access(".tmp_file", F_OK))
		unlink(".tmp_file");
	var_her->fd_write = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var_her->fd_write < 0)
	{
		print_err("heredoc: failed to open for writing");
		exit(1);
	}
	fd_collec(var_her->fd_write, 1);
	var_her->fd_read = open(".tmp_file", O_RDONLY);
	if (var_her->fd_read < 0)
	{
		print_err("heredoc input error");
		exit(1);
	}
	fd_collec(var_her->fd_read, 1);
	unlink(".tmp_file");
	exec->in_file = var_her->fd_read;
}

void	child_herdoc(char *delimiter, t_her *var_her, int quotes, t_env *env)
{
	while (1)
	{
		var_her->line = readline("> ");
		if (!var_her->line)
			print_err("warning: here-document delimited by end-of-file");
		if (!var_her->line || !ft_strcmp(delimiter, var_her->line))
		{
			free(var_her->line);
			break ;
		}
		if (ft_strchr(var_her->line, '$') && !quotes)
		{
			var_her->tmp = handel_afterd_inherdoc(var_her->line, env);
			write(var_her->fd_write, var_her->tmp, ft_strlen(var_her->tmp));
			write(var_her->fd_write, "\n", 1);
			free(var_her->line);
		}
		else
		{
			write(var_her->fd_write, var_her->line, ft_strlen(var_her->line));
			write(var_her->fd_write, "\n", 1);
			free(var_her->line);
		}
	}
	(close(var_her->fd_read), close(var_her->fd_write), exit(0));
}

int	heredoc(char *delimiter, int quotes, t_execution *exec, t_env *env)
{
	t_her	var_her;

	signal(SIGINT, SIG_IGN);
	heredoc_1(exec, &var_her);
	var_her.pid = fork();
	if (var_her.pid == 0)
	{
		signal_handler(2, env);
		child_herdoc(delimiter, &var_her, quotes, env);
	}
	else
	{
		waitpid(var_her.pid, &var_her.exit_status, 0);
		signal_handler(1, env);
		if (WEXITSTATUS(var_her.exit_status) == 130)
		{
			set_exit_status(&env, 130);
			fd_collec(0, 0);
			return (0);
		}
	}
	close(var_her.fd_write);
	return (1);
}
