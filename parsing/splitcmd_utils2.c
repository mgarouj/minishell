/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:14:40 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/28 13:57:04 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_skip_token(t_tokenn *tmp, t_tokenn *prev)
{
	if (prev && is_redirection(prev->type))
		return (1);
	if (tmp->value && tmp->value[0] == '\0' && !tmp->quotes)
		return (1);
	return (0);
}

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
