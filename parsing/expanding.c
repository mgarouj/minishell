/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:24:34 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/26 16:06:53 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_double_quote(char *exp, int *i, char *result,
		t_expand_data *data)
{
	(*i)++;
	while (exp[*i] && exp[*i] != '"')
	{
		if (exp[*i] == '$' && data->sh_expand && exp[(*i) + 1] != '"'
			&& exp[(*i) + 1] != ' ' && exp[(*i) + 1] != '\t' && exp[(*i)
				+ 1] != ',')
		{
			(*i)++;
			result = expand_variable(exp, i, result, data);
		}
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
	else
		*result = expand_variable(exp, i, *result, data);
}

char	*handel_afterd(char *exp, t_expand_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (exp[i])
	{
		if (exp[i] == '\'')
			result = handle_single_quote(exp, &i, result);
		else if (exp[i] == '"')
		{
			data->quoted = 1;
			result = handle_double_quote(exp, &i, result, data);
		}
		else if (exp[i] == '$' && data->sh_expand && exp[i + 1] && exp[i
				+ 1] != ' ' && exp[i + 1] != '\t' && exp[i + 1] != ',')
			handel_specials(&result, exp, data, &i);
		else
		{
			result = str_append_char(result, exp[i]);
			i++;
		}
	}
	return (result);
}

void	retoken(t_tokenn *token)
{
	char		**split;
	t_tokenn	*new_node;
	t_tokenn	*t;
	int			i;

	split = ft_split_whitespace(token->value);
	if (!split || !split[0])
		return ;
	free(token->value);
	token->value = ft_strdup(split[0]);
	t = token;
	i = 1;
	while (split[i])
	{
		new_node = gar_coll(sizeof(t_tokenn), 'a');
		if (!new_node)
			return ;
		new_node->type = EXP;
		new_node->value = ft_strdup(split[i]);
		new_node->next = t->next;
		t->next = new_node;
		t = new_node;
		i++;
	}
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
	while (tmp)
	{
		if (tmp->type == EXP)
		{
			if(prev && (prev->type == REDIRECTION_IN || prev->type == REDIRECTION_OUT || prev->type == REDIRECTION_AP))
			{
				print_err("ambiguous redirect");
				return(0);
			}
			data.sh_expand = !(prev && prev->type == HEREDOC);
			tmp->value = handel_afterd(tmp->value, &data);
		}
		if (data.expanded && !(data.quoted) && (ft_strchr(tmp->value, ' ')
				|| ft_strchr(tmp->value, '\t')))
			retoken(tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	return(1);
}
