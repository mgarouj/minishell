/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_one_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:36:51 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/28 14:17:38 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtins(t_execution *cmd, t_env **env)
{
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd(env));
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (ft_cd(cmd->cmd, *env));
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (ft_env(cmd->cmd, env));
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (ft_export(cmd->cmd, env));
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd->cmd));
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(cmd->cmd, env));
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (ft_exit(cmd->cmd, 0));
	return (1);
}

void	execute_one_builtin(t_execution *cmd, t_env **env)
{
	int	exit_status;
	int	backup_in;
	int	backup_out;

	if (cmd->in_file != 0 || cmd->out_file != 1)
	{
		backup_in = dup(0);
		backup_out = dup(1);
		change_in_out(cmd);
	}
	exit_status = execute_builtins(cmd, env);
	set_exit_status(1, exit_status);
	if (cmd->in_file != 0 || cmd->out_file != 1)
		restore_std(backup_in, backup_out);
}

void	child_for_one_cmd(t_execution *cmd, t_env **env)
{
	char		*path;
	struct stat	st;

	if (cmd->cmd && !ft_strcmp(cmd->cmd[0], ".."))
		(print_err("command not found"), exit(127));
	path = find_path(cmd, env);
	handle_invalid_path(cmd, env, path);
	cmd->path = path;
	cmd->env = change_envlist_to_envchar(*env);
	signal_handler(0);
	if (execve(cmd->path, cmd->cmd, cmd->env) == -1)
		handle_execve_error(cmd, &st);
}

void	execute_execve_cmd(t_execution *cmd, t_env **env)
{
	pid_t	pid;
	int		exit_status;
	int		backup_in;
	int		backup_out;

	// if (cmd->skip)
	// 	return ;
	if (cmd->in_file != 0 || cmd->out_file != 1)
	{
		backup_in = dup(0);
		backup_out = dup(1);
		change_in_out(cmd);
	}
	pid = ft_fork("fork one cmd");
	if (!pid)
		child_for_one_cmd(cmd, env);
	else
	{
		wait(&exit_status);
		if (cmd->in_file != 0 || cmd->out_file != 1)
			restore_std(backup_in, backup_out);
		handle_execve_exit(exit_status, env);
	}
}
