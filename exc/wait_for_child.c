#include "../minishell.h"


void printf_path_error(t_execution *cmd)
{
    if (!cmd->path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->cmd[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
}

void ft_wait_child(t_execution *cmd, int *exit_status)
{
    while (cmd)
	{
		waitpid(cmd->pid, exit_status, 0);
		cmd = cmd->next;
	}
}
