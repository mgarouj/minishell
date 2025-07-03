/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:17:37 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/03 15:51:18 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_tmp_filename(void)
{
	void	*m;
	char	*rnd;
	char	*file_name;

	m = gar_coll(1, 1);
	rnd = ft_itoa((long)m);
	file_name = ft_strjoin("/tmp/.tmp_file", rnd);
	if (!file_name)
	{
		print_err("heredoc: failed to generate filename");
		exit(1);
	}
	if (!access(file_name, F_OK))
		unlink(file_name);
	return (file_name);
}

void	heredoc_1(t_execution *exec, t_her *var_her)
{
	char	*file_name;

	file_name = generate_tmp_filename();
	var_her->fd_write = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var_her->fd_write < 0)
	{
		print_err("heredoc: failed to open for writing");
		exit(1);
	}
	fd_collec(var_her->fd_write, 1);
	var_her->fd_read = open(file_name, O_RDONLY);
	if (var_her->fd_read < 0)
	{
		print_err("heredoc input error");
		close(var_her->fd_write);
		exit(1);
	}
	fd_collec(var_her->fd_read, 1);
	unlink(file_name);
	exec->in_file = var_her->fd_read;
	fd_collec(exec->in_file, 1);
}

int	handle_line_input(char *delimiter, t_her *var_her, int quotes, t_env *env)
{
	if (!ft_strcmp(delimiter, var_her->line))
	{
		free(var_her->line);
		close(var_her->fd_write);
		close(var_her->fd_read);
		return (0);
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
	return (1);
}

void	child_herdoc(char *delimiter, t_her *var_her, int quotes, t_env *env)
{
	while (1)
	{
		var_her->line = readline("> ");
		if (!var_her->line)
		{
			print_err("warning: here-document delimited by end-of-file");
			close(var_her->fd_write);
			close(var_her->fd_read);
			break ;
		}
		if (!handle_line_input(delimiter, var_her, quotes, env))
			break ;
	}
	exit(0);
}

int	heredoc(char *delimiter, int quotes, t_execution *exec, t_env *env)
{
	t_her	var_her;

	signal(SIGINT, SIG_IGN);
	heredoc_1(exec, &var_her);
	var_her.pid = fork();
	if (var_her.pid == 0)
	{
		signal_handler(2);
		child_herdoc(delimiter, &var_her, quotes, env);
	}
	else
	{
		waitpid(var_her.pid, &var_her.exit_status, 0);
		signal_handler(1);
		close(var_her.fd_write);
		if (WEXITSTATUS(var_her.exit_status) == 130)
		{
			exit_status(1, 130);
			fd_collec(0, 0);
			return (0);
		}
	}
	return (1);
}
