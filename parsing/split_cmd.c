/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:09:09 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/28 18:47:49 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredocs_only(t_tokenn **tmp, t_execution *exec, t_env *env)
{
	while (*tmp && (*tmp)->type != PIPE)
	{
		if ((*tmp)->type == HEREDOC)
		{
			if (!(*tmp)->next || !heredoc((*tmp)->next->value,
					(*tmp)->next->quotes, exec, env))
				return (0);
			*tmp = (*tmp)->next;
		}
		*tmp = (*tmp)->next;
	}
	return (1);
}

int	init_exec_list(t_tokenn **tmp, t_execution **exec_list, t_env *env)
{
	t_execution	*exec;
	t_tokenn	*here;
	int			c;

	initialize(&here, *tmp, &c);
	while (here)
	{
		if ((here)->type == HEREDOC)
			c++;
		(here) = (here)->next;
	}
	if (!check_c_heredoc(c))
		return (0);
	while (*tmp)
	{
		exec = creat_node((*tmp)->expan_toex);
		if (!exec)
			return (0);
		if (!handle_heredocs_only(tmp, exec, env))
			return (0);
		add_node_to_list(exec_list, exec);
		if (*tmp && (*tmp)->type == PIPE)
			*tmp = (*tmp)->next;
	}
	return (1);
}

int	handel_all_redi(t_tokenn *token, t_execution *exec)
{
	t_tokenn	*tmp;

	tmp = token;
	while (tmp && (tmp)->type != PIPE)
	{
		if (is_redirection(tmp->type))
		{
			if (tmp->type != HEREDOC && (!tmp->next || !handel_redirections(tmp,
						tmp->next, exec)))
			{
				set_exit_status(1, 1);
				return (0);
			}
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	handel_all_cmd(t_tokenn *token, t_execution *exec)
{
	t_tokenn	*tmp;
	t_tokenn	*prev;

	tmp = token;
	prev = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == EXP)
		{
			if (should_skip_token(tmp, prev))
			{
				prev = tmp;
				tmp = tmp->next;
				continue ;
			}
			if (!append_to_cmd(tmp->value, exec))
				return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	split_cmd(t_tokenn *token, t_execution **exec_list, t_env *env)
{
	t_tokenn	*tmp;
	t_execution	*iter;

	tmp = token;
	if (!init_exec_list(&tmp, exec_list, env))
		return (0);
	tmp = token;
	iter = *exec_list;
	while (tmp && iter)
	{
		iter->skip = 0;
		if (!handel_all_redi(tmp, iter))
			iter->skip = 1;
		if (!handel_all_cmd(tmp, iter))
			return (0);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		iter = iter->next;
	}
	return (1);
}
