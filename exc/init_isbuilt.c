#include "../minishell.h"

int ft_isbuilt(t_execution *cmd)
{
    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return 0;
    if (ft_strcmp(cmd->cmd[0], "env") == 0)
        return (1);
    else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
        return (1);
    else if (ft_strcmp(cmd->cmd[0], "export") == 0)
        return (1);
    else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
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


void is_last(t_execution **cmd_list)
{
    t_execution *tmp = *cmd_list;
    
    while (tmp)
    {
        if (!tmp->next)
            tmp->is_last = true;
        else
            tmp->is_last = false;
        tmp = tmp->next;
    }
}

// void init_isfirst(t_execution **cmd_list)
// {
//     t_execution *tmp_cmd;

//     tmp_cmd = *cmd_list;
//     tmp_cmd->is_first = 1;
//     tmp_cmd = tmp_cmd->next;
//     while (tmp_cmd)
//     {
//         tmp_cmd->is_first = 0;
//         tmp_cmd = tmp_cmd->next;
//     }
// }

void init_cmd(t_execution **cmd_list, int n_cmds)
{
    is_built(cmd_list);
    if (n_cmds > 1)
        is_last(cmd_list);
    // init_isfirst(cmd_list);
}