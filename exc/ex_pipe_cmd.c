/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:36:58 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/26 20:36:29 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_in_out(int prev_read, t_execution *cmd)
{
	if (prev_read != -1)
	{
		dup2(prev_read, 0);
		close(prev_read);
	}
	if (!cmd->is_last)
	{
		close(cmd->pipe_fd[0]);
		dup2(cmd->pipe_fd[1], 1);
		close(cmd->pipe_fd[1]);
	}
	if (cmd->in_file != 0)
	{
		dup2(cmd->in_file, 0);
		close(cmd->in_file);
	}
	if (cmd->out_file != 1)
	{
		dup2(cmd->out_file, 1);
		close(cmd->out_file);
	}
}

void	child_run_cmd(t_execution *cmd, t_env **env)
{
	int	status;

	if (cmd->is_builtin)
	{
		status = execute_builtins(cmd, env);
		exit(status);
	}
	else
	{
		cmd->path = find_path(cmd, env);
		printf_path_error(cmd);
		execve(cmd->path, cmd->cmd, cmd->env);
		perror("execve");
		exit(1);
	}
}

int	handle_parent(t_execution *cmd, int prev_read)
{
	if (prev_read != -1)
		close(prev_read);
	if (!cmd->is_last)
	{
		close(cmd->pipe_fd[1]);
		return (cmd->pipe_fd[0]);
	}
	return (-1);
}

void	set_exit_status(t_env **env, int exit_status)
{
	t_env	*tmp_env;

	tmp_env = *env;
	tmp_env->exit_status = exit_status;
}

void	execute_pipe_cmd(t_execution **list_cmd, t_env **env)
{
	t_execution	*tmp_cmd;
	int			prev_read;
	int			exit_status;

	tmp_cmd = *list_cmd;
	prev_read = -1;
	while (tmp_cmd)
	{
		if (tmp_cmd->is_last == false)
			pipe(tmp_cmd->pipe_fd);
		tmp_cmd->pid = ft_fork("fork in pipe");
		if (!tmp_cmd->pid)
		{
			child_in_out(prev_read, tmp_cmd);
			child_run_cmd(tmp_cmd, env);
		}
		else
			prev_read = handle_parent(tmp_cmd, prev_read);
		tmp_cmd = tmp_cmd->next;
	}
	tmp_cmd = *list_cmd;
	ft_wait_child(tmp_cmd, &exit_status);
	set_exit_status(env, WEXITSTATUS(exit_status));
}
