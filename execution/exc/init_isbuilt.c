#include "../minishell.h"

int ft_isbuilt(t_execution *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (1);
	return (0);
}

void is_built(t_execution **cmd_list)
{
	t_execution *tmp;

	tmp = *cmd_list;
	while (tmp)
	{
		if (ft_isbuilt(tmp))
			tmp->is_builtin = 1;
		else
			tmp->is_builtin = 0;
		tmp = tmp->next;
	}
}

void init_cmd(t_execution **cmd_list)
{
	is_built(cmd_list);
}