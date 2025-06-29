/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:15:38 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/29 14:50:55 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_path_error(t_execution *cmd, t_env *env)
{
	if (!cmd->path)
	{
		if (access(cmd->cmd[0], X_OK) == -1 && !get_env_value("PATH", env))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->cmd[0], 2);
			perror(" ");
			if (access(cmd->cmd[0], F_OK) == -1)
				exit(127);
			exit(126);
		}
		else if (access(cmd->cmd[0], X_OK) == 0 && !get_env_value("PATH", env))
			exit(0);
		print_err_ex(": command not found", cmd->cmd[0]);
		exit(127);
	}
	if (!ft_strcmp(cmd->path, "pr_dn"))
	{
		print_err_ex(": Permission denied", cmd->cmd[0]);
		exit(126);
	}
}

void	ft_wait_child(t_execution *cmd, int *exit_status)
{
	while (cmd)
	{
		waitpid(cmd->pid, exit_status, 0);
		cmd = cmd->next;
	}
}

void	handle_pipe_exit(t_execution **list_cmd, t_env **env, int *status)
{
	t_execution	*tmp_cmd;

	tmp_cmd = *list_cmd;
	(void)env;
	ft_wait_child(tmp_cmd, status);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		set_exit_status(1, 130);
	}
	else if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		set_exit_status(1, 131);
	}
	else if (WIFEXITED(*status))
		set_exit_status(1, WEXITSTATUS(*status));
}

void	handle_execve_exit(int status, t_env **env)
{
	int	sig;

	(void)env;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			set_exit_status(1, 130);
		}
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			set_exit_status(1, 131);
		}
	}
	else if (WIFEXITED(status))
		set_exit_status(1, WEXITSTATUS(status));
}
