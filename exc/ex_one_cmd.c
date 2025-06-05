/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_one_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:36:51 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/29 18:30:38 by mgarouj          ###   ########.fr       */
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
	set_exit_status(env, exit_status);
	if (cmd->in_file != 0 || cmd->out_file != 1)
		restore_std(backup_in, backup_out);
}

char	**change_envlist_to_envchar(t_env *env)
{
	t_env	*tmp;
	char	**env_array;
	char	*joined;
	int		i;
	int		size;

	tmp = env;
	size = ft_lstsize(env);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			joined = ft_strjoin_3(tmp->key, tmp->value);
			env_array[i++] = joined;
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	child_for_one_cmd(t_execution *cmd, t_env **env)
{
	char	*path;

	path = find_path(cmd, env);
	if (!path)
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	cmd->path = path;
	cmd->env = change_envlist_to_envchar(*env);
	signal_handler(0);
	if (execve(cmd->path, cmd->cmd, cmd->env) == -1)
	{
		if (!ft_strcmp(cmd->cmd[0],".."))
			print_err("command not found");
		else
			perror("execve");
		exit (127);
	}
}

void	execute_execve_cmd(t_execution *cmd, t_env **env)
{
	pid_t	pid;
	int		exit_status;
	int		backup_in;
	int		backup_out;

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
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
			write(1, "\n", 1);
		if (WIFEXITED(exit_status))
			set_exit_status(env, WEXITSTATUS(exit_status));
	}
}
