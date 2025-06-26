/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:24:34 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 16:17:10 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_whitespace(char *value)
{
	while (*value)
	{
		if (*value == ' ' || *value == '\t')
			return (1);
		value++;
	}
	return (0);
}

int	needs_retokenn(char *value, int quoted, t_context_type ctx)
{
	char	*eq;

	eq = ft_strchr(value, '=');
	if (ctx == CTX_COMMAND_ARG)
		return (has_whitespace(value) && !quoted);
	if (eq == value)
		return (1);
	if (quoted)
		return (0);
	if (ctx == CTX_EXPORT_DIRECT)
		return (has_whitespace(value));
	if (ctx == CTX_EXPORT_RHS)
		return (0);
	return (0);
}

static int	handle_token_expand(t_tokenn *tmp, t_tokenn *prev,
		t_expand_data *data, t_env *env)
{
	t_context_type	ctx;

	ctx = CTX_COMMAND_ARG;
	if (prev && prev->type == EXP && !ft_strcmp(prev->value, "export"))
	{
		if (tmp->value[0] == '$')
			ctx = CTX_EXPORT_DIRECT;
		else
			ctx = CTX_EXPORT_RHS;
	}
	if (!handle_expand_token(tmp, prev, data, env))
		return (0);
	if (data->expanded && needs_retokenn(tmp->value, data->quoted, ctx)
		&& (ft_strchr(tmp->value, ' ') || ft_strchr(tmp->value, '\t')))
	{
		if (!retokenn(tmp))
			return (0);
	}
	tmp->expan_toex = data->expanded_toexe;
	return (1);
}

int	expand_rm_quotes(t_tokenn *t, t_env *env)
{
	t_tokenn		*tmp;
	t_tokenn		*prev;
	t_expand_data	data;

	tmp = t;
	prev = NULL;
	data.env = env;
	data.expanded = 0;
	data.quoted = 0;
	data.expanded_toexe = 0;
	while (tmp)
	{
		if (tmp->type == EXP)
		{
			if (!handle_token_expand(tmp, prev, &data, env))
				return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}
