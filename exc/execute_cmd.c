/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:12:37 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/31 17:59:39 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_one_cmd(t_execution **cmd_list, t_env **list_env)
{
	t_execution	*tmp_cmd;

	tmp_cmd = *cmd_list;
	if (tmp_cmd->cmd && tmp_cmd->is_builtin)
		execute_one_builtin(tmp_cmd, list_env);
	else
		execute_execve_cmd(tmp_cmd, list_env);
}

void init_pwd(t_env **env)
{
	t_env *e;

	e = *env;
	e->pwd = ft_strdup(get_env_value("PWD", e));
}

void	execute_cmd(t_execution **cmd_list, t_env **list_env)
{
	int	n_cmds;

	n_cmds = ft_lstsize_cmd_list(*cmd_list);
	if (n_cmds <= 0)
		return ;
	init_cmd(cmd_list, n_cmds);
	init_pwd(list_env);
	init_env_cmd(*list_env, cmd_list);
	if (!(*cmd_list)->cmd)
		return ;
	if (n_cmds == 1)
		execute_one_cmd(cmd_list, list_env);
	else
		execute_pipe_cmd(cmd_list, list_env);
}
