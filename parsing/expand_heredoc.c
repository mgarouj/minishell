/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:57:49 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/21 21:09:37 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variable_inheredoc(char *exp, int *i, char *result, t_env *env)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (exp[*i] && !ft_strchr(" \t\"'$;%,.[]=*", exp[*i]))
		(*i)++;
	var_name = sub_str(exp + start, (*i) - start);
	var_value = get_env_value(var_name, env);
	if (var_value)
		result = str_append(result, var_value);
	return (result);
}

void	handel_specials_inheredoc(char **result, char *exp, t_env *env, int *i)
{
	(*i)++;
	if (exp[*i] == '$')
	{
		(*i)++;
	}
	else if (exp[*i] == '?')
	{
		*result = str_append(*result, ft_itoa(set_exit_status(0,0)));
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
		*result = expand_variable_inheredoc(exp, i, *result, env);
}

char	*handel_afterd_inherdoc(char *exp, t_env *env)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (exp[i])
	{
		if (exp[i] == '$' && exp[i + 1] && !ft_strchr(" \t,:=+", exp[i + 1]))
			handel_specials_inheredoc(&result, exp, env, &i);
		else
		{
			result = str_append_char(result, exp[i]);
			i++;
		}
	}
	return (result);
}
