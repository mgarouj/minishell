/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:09:09 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/31 17:51:37 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_to_cmd(char *exp, t_execution *exec)
{
	char	**new_cmd;
	int		required_size;

	if (!exp || !exec)
		return (0);
	required_size = calculate_required_size(exp, exec);
	new_cmd = gar_coll(sizeof(char *) * required_size, 'a');
	if (!new_cmd)
		return (0);
	if (!copy_and_append_cmd(new_cmd, exec, exp))
		return (0);
	exec->cmd = new_cmd;
	return (1);
}

int	handel_redirections(t_tokenn *token, char *file_name, t_execution *exec,t_env *env)
{
	if (token->type == REDIRECTION_IN)
		return (handel_redin(file_name, exec));
	else if (token->type == REDIRECTION_OUT)
		return (handel_reout(file_name, exec));
	else if (token->type == REDIRECTION_AP)
		return (handel_redappend(file_name, exec));
	else if (token->type == HEREDOC)
		return (handle_heredoc(file_name, exec,env));
	return (0);
}

static int	process_command(t_tokenn **tmp, t_execution *exec,t_env *env)
{
	while (*tmp && (*tmp)->type != PIPE)
	{
		if ((*tmp)->type == EXP && (*tmp)->value)
		{
			if (!append_to_cmd((*tmp)->value, exec))
				return (0);
		}
		else if (is_redirection((*tmp)->value))
		{
			if (!(*tmp)->next || !handel_redirections(*tmp, (*tmp)->next->value,
					exec,env))
			{
				print_err("No such file or directory");
				return (0);
			}
			*tmp = (*tmp)->next;
		}
		*tmp = (*tmp)->next;
	}
	return (1);
}

int	split_cmd(t_tokenn *token, t_execution **exec_list,t_env *env)
{
	t_tokenn	*tmp;
	t_execution	*exec;

	tmp = token;
	while (tmp)
	{
		exec = creat_node();
		if (!exec)
			return (0);
		if (!process_command(&tmp, exec,env))
			return (0);
		add_node_to_list(exec_list, exec);
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
	return (1);
}
