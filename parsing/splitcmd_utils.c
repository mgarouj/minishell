/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:27:47 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/24 18:33:15 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execution	*creat_node(void)
{
	t_execution	*exec;

	exec = gar_coll(sizeof(t_execution), 'a');
	exec->cmd = NULL;
	exec->in_file = 0;
	exec->out_file = 1;
	exec->next = NULL;
	return (exec);
}

void	add_node_to_list(t_execution **exec, t_execution *node)
{
	t_execution	*tmp;

	if (!*exec)
	{
		*exec = node;
		return ;
	}
	tmp = *exec;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	is_redirection(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">") || !ft_strcmp(s, "<<")
		|| !ft_strcmp(s, ">>"));
}

int	calculate_required_size(char *exp, t_execution *exec)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (exp && exp[i])
		if (exp[i++] == ' ' || exp[i] == '\t')
			size++;
	if (exec->cmd)
		while (exec->cmd[size])
			size++;
	return (size + 2);
}

int	copy_and_append_cmd(char **new_cmd, t_execution *exec, char *exp)
{
	int	i;

	i = 0;
	if (exec->cmd)
	{
		while (exec->cmd[i])
		{
			new_cmd[i] = exec->cmd[i];
			i++;
		}
	}
	new_cmd[i] = ft_strdup(exp);
	if (!new_cmd[i])
		return (0);
	new_cmd[i + 1] = NULL;
	return (1);
}
