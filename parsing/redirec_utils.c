/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:00:59 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/02 14:04:35 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_writable_file(char *filename)
{
	struct stat	st;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) != 0)
			return (print_err_ex(": Permission denied", filename), 0);
		if (stat(filename, &st) == 0 && S_ISDIR(st.st_mode))
			return (print_err_ex(": Is a directory", filename), 0);
	}
	return (1);
}

char	*get_env_value(char *key, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, key) == 0)
			return (env_tmp->value);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

t_token	get_last_input_redirection(t_tokenn *start)
{
	t_tokenn	*tmp;
	t_token		last_type;

	last_type = EXP;
	tmp = start;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIRECTION_IN || tmp->type == HEREDOC)
			last_type = tmp->type;
		tmp = tmp->next;
	}
	return (last_type);
}

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
