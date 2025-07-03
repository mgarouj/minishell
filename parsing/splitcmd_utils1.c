/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:15:58 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/03 17:45:18 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_c_heredoc(int c)
{
	if (c > 16)
	{
		print_err("maximum here-document count exceeded");
		return (0);
	}
	return (1);
}

void	initialize(t_tokenn **here, t_tokenn *tmp, int *c)
{
	*c = 0;
	*here = tmp;
}

int	handel_redirections(t_tokenn *token, t_tokenn *name, t_execution *exec,
		t_token last)
{
	if (token->type == REDIRECTION_IN)
		return (handel_redin(name->value, exec, last));
	else if (token->type == REDIRECTION_OUT)
		return (handel_reout(name->value, exec));
	else if (token->type == REDIRECTION_AP)
		return (handel_redappend(name->value, exec));
	return (1);
}
