/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:09:09 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 16:20:21 by mgarouj          ###   ########.fr       */
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

// static int	process_command(t_tokenn **tmp, t_execution *exec, t_env *env)
// {
// 	while (*tmp && (*tmp)->type != PIPE)
// 	{
// 		if ((*tmp)->type == EXP && (*tmp)->value)
// 		{
// 			if (!append_to_cmd((*tmp)->value, exec))
// 				return (0);
// 		}
// 		else if (is_redirection((*tmp)->value))
// 		{
// 			if ((*tmp)->type != HEREDOC && (!(*tmp)->next
// 					|| !handel_redirections(*tmp, (*tmp)->next, exec)))
// 			{
// 				if (env->exit_status == 130)
// 					return (0);
// 				print_err("No such file or directory");
// 				return (0);
// 			}
// 			*tmp = (*tmp)->next;
// 		}
// 		*tmp = (*tmp)->next;
// 	}
// 	return (1);
// }

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

int	handel_all_redi(t_tokenn *token, t_execution *exec, t_env *env)
{
	t_tokenn	*tmp;

	tmp = token;
	while (tmp && (tmp)->type != PIPE)
	{
		if (is_redirection(tmp->value))
		{
			if (tmp->type != HEREDOC && (!tmp->next || !handel_redirections(tmp,
						tmp->next, exec)))
			{
				if (env->exit_status == 130)
				{
					set_exit_status(1,130);
					return (0);
				}
				set_exit_status(1,1);
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
			if (prev && is_redirection(prev->value))
			{
				prev = tmp;
				tmp = tmp->next;
				// do NOT update prev here, keep it as is
				continue ;
			}
			if (tmp->value && tmp->value[0] == '\0' && !tmp->quotes)
			{
				prev = tmp;
				tmp = tmp->next;
				continue; // skip unquoted empty var
			}
			if (!append_to_cmd(tmp->value, exec))
				return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

// int	handel_all_cmd(t_tokenn *token, t_execution *exec)
// {
// 	t_tokenn	*tmp;
// 	t_tokenn	*prev;

// 	tmp = token;
// 	prev = NULL;
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		printf("Token: type=%d, value='%s', quotes=%d\n", tmp->type, tmp->value, tmp->quotes);
// 		if (tmp->type == EXP)
// 		{
// 			if (prev && is_redirection(prev->value))
// 			{
// 				printf("Skipping token after redirection: '%s'\n", tmp->value);
// 				tmp = tmp->next;
// 				continue ;
// 			}
// 			if (tmp->value && tmp->value[0] == '\0' && !tmp->quotes)
// 			{
// 				printf("Skipping empty unquoted token\n");
// 				tmp = tmp->next;
// 				continue;
// 			}
// 			if (!append_to_cmd(tmp->value, exec))
// 			{
// 				printf("Failed to append token '%s'\n", tmp->value);
// 				return (0);
// 			}
// 			else
// 				printf("Appended token '%s'\n", tmp->value);
// 		}
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

int	split_cmd(t_tokenn *token, t_execution **exec_list, t_env *env)
{
	t_tokenn *tmp;
	t_execution *iter;

	tmp = token;
	if (!init_exec_list(&tmp, exec_list, env))
		return (0);
	tmp = token;
	iter = *exec_list;
	while (tmp && iter)
	{
		// Save current position to pass to redirection and command handlers
		t_tokenn *segment_start = tmp;
		iter->skip = 0;
		if (!handel_all_redi(segment_start, iter, env))
		{
			if (env->exit_status == 130)
				return (0);
			iter->skip = 1;
		}
		
		if (!handel_all_cmd(segment_start, iter))
			return (0);
		
		printf("%d\n",iter->skip);
		// Advance tmp to after the current pipeline segment
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;

		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;

		iter = iter->next;
	}

	return (1);
}