/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:07:38 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/20 21:21:20 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_append(char *s1, char *s2)
{
	char	*new_str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = gar_coll(len, 'a');
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1);
	ft_strcat(new_str, s2);
	return (new_str);
}

char	*str_append_char(char *s, char c)
{
	int		len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = gar_coll(len + 2, 'a');
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
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

char	*expand_variable(char *exp, int *i, char *result, t_expand_data *data)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (exp[*i] && !ft_strchr(" \t\"'$;%,.[]=*", exp[*i]))
		(*i)++;
	var_name = sub_str(exp + start, (*i) - start);
	var_value = get_env_value(var_name, data->env);
	if (!ft_strcmp(var_name, "PWD"))
		if (!var_value)
			var_value = data->env->pwd;
	data->expanded_toexe = 1;
	if (var_value)
	{
		data->expanded = 1;
		result = str_append(result, var_value);
	}
	return (result);
}

char	*handle_single_quote(char *exp, int *i, char *result)
{
	(*i)++;
	while (exp[*i] && exp[*i] != '\'')
	{
		result = str_append_char(result, exp[*i]);
		(*i)++;
	}
	if (exp[*i] == '\'')
		(*i)++;
	return (result);
}
