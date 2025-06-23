/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:13:08 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/22 17:19:04 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(char **path, t_execution *cmd)
{
	int		i;
	char	*test;
	char	*full;

	i = 0;
	while (path[i])
	{
		test = ft_strjoin(path[i], "/");
		full = ft_strjoin(test, cmd->cmd[0]);
		if (access(full, X_OK) == 0)
			return (full);
		i++;
	}
	return (NULL);
}

char	*find_path(t_execution *cmd, t_env **env)
{
	char	*env_path;
	char	**path;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		exit(0);
	if (ft_strchr(cmd->cmd[0], '/'))
	{
		if (access(cmd->cmd[0], F_OK) == -1)
			return (NULL);
		if (access(cmd->cmd[0], X_OK) == -1)
			return (ft_strdup("pr_dn"));
		return (ft_strdup(cmd->cmd[0]));
	}
	env_path = get_env_value("PATH", *env);
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	return (check_path(path, cmd));
}
// child_helpers.c

void	handle_invalid_path(t_execution *cmd, t_env **env, char *path)
{
	if (!path)
	{
		if (access(cmd->cmd[0], X_OK) == -1 && !get_env_value("PATH", *env))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->cmd[0], 2);
			perror(" ");
			if (access(cmd->cmd[0], F_OK) == -1)
				exit (127);
			exit(126);
		}
		else if (access(cmd->cmd[0], X_OK) == 0 && !get_env_value("PATH", *env))
			exit(0);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (!ft_strcmp(path, "pr_dn"))
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
}

void	execve_command_handler(t_execution *cmd, t_env **env)
{
	if (!ft_strcmp(cmd->cmd[0], ".."))
	{
		print_err("command not found");
		exit(127);
	}
	cmd->path = find_path(cmd, env);
	printf_path_error(cmd, *env);
	signal_handler(0, *env);
	if (execve(cmd->path, cmd->cmd, cmd->env) == -1)
	{
		if (!access(cmd->cmd[0], X_OK))
			exit(0);
		if (cmd->flag_expand == 1 && !ft_strcmp(cmd->cmd[0], ""))
			exit(0);
		else if (cmd->flag_expand == 0 && !ft_strcmp(cmd->cmd[0], ""))
		{
			print_err("command not found");
			exit(127);
		}
		perror("minishell ");
		exit(1);
	}
}
