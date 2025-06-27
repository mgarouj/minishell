/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:01:08 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/27 14:53:20 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	retokenn(t_tokenn *token)
{
	char		**split;
	t_tokenn	*new_node;
	t_tokenn	*t;
	int			i;

	split = ft_split_whitespace(token->value);
	if (!split || !split[0])
		return (0);
	token->value = ft_strdup(split[0]);
	t = token;
	i = 1;
	while (split[i])
	{
		new_node = gar_coll(sizeof(t_tokenn), 'a');
		if (!new_node)
			return (0);
		new_node->type = EXP;
		new_node->value = ft_strdup(split[i]);
		new_node->next = t->next;
		t->next = new_node;
		t = new_node;
		i++;
	}
	return (1);
}

int	handle_expand_token(t_tokenn *tmp, t_tokenn *prev, t_expand_data *data,
		t_env *env)
{
	(void ) env;
	data->sh_expand = !(prev && prev->type == HEREDOC);
	if (ft_strchr(tmp->value, '$') && !tmp->quotes)
	{
		if (prev && (prev->type == REDIRECTION_IN
				|| prev->type == REDIRECTION_OUT
				|| prev->type == REDIRECTION_AP))
		{
			tmp->value = handel_afterd(tmp->value, data);
			if (!tmp->value || ft_strchr(tmp->value, ' ')
				|| ft_strchr(tmp->value, '\t') || tmp->value[0] == '\0')
			{
				print_err("ambiguous redirect");
				set_exit_status(1, 2);
				return (0);
			}
		}
		else
			tmp->value = handel_afterd(tmp->value, data);
	}
	else
		tmp->value = handel_afterd(tmp->value, data);
	return (1);
}

void	handel_specials(char **result, char *exp, t_expand_data *data, int *i)
{
	(*i)++;
	if (exp[*i] == '$')
	{
		(*i)++;
	}
	else if (exp[*i] == '?')
	{
		*result = str_append(*result, ft_itoa(data->env->exit_status));
		(*i)++;
	}
	else if (is_num(exp[*i]))
	{
		(*i)++;
		while (exp[*i])
		{
			*result = str_append_char(*result, exp[*i]);
			(*i)++;
		}
	}
	else
		*result = expand_variable(exp, i, *result, data);
}

char	*handle_double_quote(char *exp, int *i, char *result,
		t_expand_data *data)
{
	(*i)++;
	while (exp[*i] && exp[*i] != '"')
	{
		if (exp[*i] == '$' && data->sh_expand && exp[*i + 1]
			&& !ft_strchr(" \t,:=+\"", exp[*i + 1]))
			handel_specials(&result, exp, data, i);
		else
		{
			result = str_append_char(result, exp[*i]);
			(*i)++;
		}
	}
	if (exp[*i] == '"')
		(*i)++;
	return (result);
}

char	*handel_afterd(char *exp, t_expand_data *data)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (exp[i])
	{
		if (exp[i] == '\'')
		{
			data->quoted = 1;
			result = handle_single_quote(exp, &i, result);

		}
		else if (exp[i] == '"')
		{
			result = handle_double_quote(exp, &i, result, data);
		}
		else if (exp[i] == '$' && data->sh_expand && exp[i + 1]
			&& !ft_strchr(" \t,:=+/", exp[i + 1]))
			handel_specials(&result, exp, data, &i);
		else
			result = str_append_char(result, exp[i++]);
	}
	if (ft_strlen(result) == 0)
		result = ft_strdup("\0");
	return (result);
}
