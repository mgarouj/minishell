#include "../minishell.h"

void    execute_one_cmd(t_execution **cmd_list, t_env **list_env)
{
    t_execution *tmp_cmd;

    tmp_cmd = *cmd_list;
    if (tmp_cmd->cmd && tmp_cmd->is_builtin)
        execute_one_builtin(tmp_cmd, list_env);
    else
        execute_execve_cmd(tmp_cmd, list_env);
}

void execute_cmd(t_execution **cmd_list, t_env **list_env)
{
    int n_cmds = ft_lstsize_cmd_list(*cmd_list);

    if (n_cmds <= 0)
        return ; 

    init_cmd(cmd_list, n_cmds);

    if (n_cmds == 1)
        execute_one_cmd(cmd_list, list_env);
    else
        execute_pipe_cmd(cmd_list, list_env, n_cmds);
}