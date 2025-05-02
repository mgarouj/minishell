// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expanding.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/11 19:35:36 by fbelkass          #+#    #+#             */
// /*   Updated: 2025/05/02 20:32:41 by fbelkass         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// char	*str_append(char *s1, char *s2)
// {
// 	char	*new_str;
// 	int		len;

// 	len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	new_str = gar_coll(len, 'a', 1);
// 	if (!new_str)
// 		return (NULL);
// 	ft_strcpy(new_str, s1);
// 	ft_strcat(new_str, s2);
// 	return (new_str);
// }

// // Memory Reallocation in str_append: Every time you append to result using 
// // str_append or str_append_char, result is reassigned to a new memory location 
// // that holds the old contents plus the new content.

// char	*str_append_char(char *s, char c)
// {
// 	int		len;
// 	char	*new_str;

// 	len = ft_strlen(s);
// 	new_str = gar_coll(len + 2, 'a', 1);
// 	if (!new_str)
// 		return (NULL);
// 	ft_strcpy(new_str, s);
// 	new_str[len] = c;
// 	new_str[len + 1] = '\0';
// 	return (new_str);
// }

// char	*get_env_value(char *key, t_env *env)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, key) == 0)
// 			return (env->value);
// 		env = env->next;
// 	}
// 	return (NULL);
// }


// char	*expand_variable(char *exp, int *i, t_env *env, char *result)
// {
// 	int		start;
// 	char	*var_name;
// 	char	*var_value;

// 	start = *i;
// 	while (exp[*i] && exp[*i] != ' ' && exp[*i] != '\t' && exp[*i] != '"'
// 		&& exp[*i] != '\'' && exp[*i] != '$')
// 		(*i)++;
// 	var_name = sub_str(exp + start, (*i) - start);
// 	var_value = get_env_value(var_name, env);
// 	if (var_value)
// 		result = str_append(result, var_value);
//     return(result);
// }

// char	*handle_single_quote(char *exp, int *i, char *result)
// {
// 	(*i)++;
// 	while (exp[*i] && exp[*i] != '\'')
// 	{
// 		result = str_append_char(result, exp[*i]);
// 		(*i)++;
// 	}
// 	if (exp[*i] == '\'')
// 		(*i)++;
// 	return (result);
// }

// char	*handle_double_quote(char *exp, int *i, char *result, t_env *env)
// {
// 	(*i)++;
// 	while (exp[*i] && exp[*i] != '"')
// 	{
// 		// if (exp[*i] == '$')
//         // {
//         //     (*i)++;
//         //     result = expand_variable(exp, i, env, result);
//         // }
// 		// else
//         // {
//             result = str_append_char(result, exp[*i]);
// 		    (*i)++;
//         // }
// 	}
//     if(exp[*i] == '"')
//         (*i)++;
//     return(result);
// }

// char	*handel_afterd(char *exp, t_env *env)
// {
// 	int		i;
// 	char	*result;

// 	result = ft_strdup("");
// 	i = 0;
// 	while (exp[i])
// 	{
// 		if (exp[i] == '\'')
// 			result = handle_single_quote(exp, &i, result);
// 		else if (exp[i] == '"')
//             result = handle_double_quote(exp,&i,result,env);
//         // else if(exp[i] == '$')
//         // {
//         //     i++;
//         //     result = expand_variable(exp,&i,env,result);
//         // }
//         else
//         {
//             result = str_append_char(result,exp[i]);
//             i++;
//         }
// 	}
//     return(result);
// }

// void	remove_quotes(t_tokenn *t, t_env *l)
// {
// 	t_tokenn	*tmp;
//     char *expanded;
    
// 	tmp = t;
// 	while (tmp)
// 	{
// 		if (tmp->type == EXP)
// 		{
// 			expanded = handel_afterd(tmp->value, l);
//             tmp->value = expanded;
// 		}
// 		tmp = tmp->next;
// 	}
// }



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:35:36 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/02 20:52:00 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_append(char *s1, char *s2)
{
	char	*new_str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = gar_coll(len, 'a', 1);
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
	new_str = gar_coll(len + 2, 'a', 1);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expand_variable(char *exp, int *i, t_env *env, char *result)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (exp[*i] && exp[*i] != ' ' && exp[*i] != '\t' && exp[*i] != '"'
		&& exp[*i] != '\'' && exp[*i] != '$')
		(*i)++;
	var_name = sub_str(exp + start, (*i) - start);
	var_value = get_env_value(var_name, env);
	if (var_value)
		result = str_append(result, var_value);
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

char	*handle_double_quote(char *exp, int *i, char *result, t_env *env, int expand)
{
	(*i)++;
	while (exp[*i] && exp[*i] != '"')
	{
		if (exp[*i] == '$' && expand)
		{
			(*i)++;
			result = expand_variable(exp, i, env, result);
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

char	*handel_afterd(char *exp, t_env *env, int expand)
{
	int		i = 0;
	char	*result = ft_strdup("");

	while (exp[i])
	{
		if (exp[i] == '\'')
			result = handle_single_quote(exp, &i, result);
		else if (exp[i] == '"')
			result = handle_double_quote(exp, &i, result, env, expand);
		else if (exp[i] == '$' && expand)
		{
			i++;
			result = expand_variable(exp, &i, env, result);
		}
		else
		{
			result = str_append_char(result, exp[i]);
			i++;
		}
	}
	return (result);
}

void	remove_quotes(t_tokenn *t, t_env *env)
{
	t_tokenn	*tmp = t;
	t_tokenn	*prev = NULL;

	while (tmp)
	{
		if (tmp->type == EXP)
		{
			int expand = !(prev && prev->type == HEREDOC);
			tmp->value = handel_afterd(tmp->value, env, expand);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
