#include "../minishell.h"

void	execve_command_handler(t_execution *cmd, t_env **env)
{
	struct stat	st;

	if (cmd->cmd && !ft_strcmp(cmd->cmd[0], ".."))
	{
		print_err_ex(": command not found", cmd->cmd[0]);
		exit(127);
	}
	cmd->path = find_path(cmd, env);
	handle_invalid_path(cmd, env, cmd->path);
	signal_handler(0, *env);
	if (execve(cmd->path, cmd->cmd, cmd->env) == -1)
		handle_execve_error(cmd, &st);
}
