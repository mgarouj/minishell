/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:24:34 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/17 16:48:56 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *str_append(char *s1, char *s2)
{
    char    *new_str;
    int        len;

    len = ft_strlen(s1) + ft_strlen(s2) + 1;
    new_str = gar_coll(len, 'a');
    if (!new_str)
        return (NULL);
    ft_strcpy(new_str, s1);
    ft_strcat(new_str, s2);
    return (new_str);
}

char    *str_append_char(char *s, char c)
{
    int        len;
    char    *new_str;

    len = ft_strlen(s);
    new_str = gar_coll(len + 2, 'a');
    if (!new_str)
        return (NULL);
    ft_strcpy(new_str, s);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return (new_str);
}

char    *get_env_value(char *key, t_env *env)
{
    t_env *env_tmp;

    env_tmp = env;
    while (env_tmp)
    {
        if (ft_strcmp(env_tmp->key, key) == 0)
            return (env_tmp->value);
        env_tmp = env_tmp->next;
    }
    return (NULL);
}

char    *expand_variable(char *exp, int *i, t_env *env, char *result)
{
    int        start;
    char    *var_name;
    char    *var_value;

    start = *i;
    while (exp[*i] && exp[*i] != ' ' && exp[*i] != '\t' && exp[*i] != '"'
        && exp[*i] != '\'' && exp[*i] != '$' && exp[*i] != ',' && exp[*i] != ';')
        (*i)++;
    var_name = sub_str(exp + start, (*i) - start);
    var_value = get_env_value(var_name, env);
    if (var_value)
        result = str_append(result, var_value);
    return (result);
}

char    *handle_single_quote(char *exp, int *i, char *result)
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

char    *handle_double_quote(char *exp, int *i, char *result, t_env *env, int expand)
{
    (*i)++;
    while (exp[*i] && exp[*i] != '"')
    {
        if (exp[*i] == '$' && expand && exp[(*i) + 1]!='"' && exp[(*i) + 1] != ' ' && exp[(*i) + 1] != '\t' && exp[(*i) + 1] != ',')
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

char    *handel_afterd(char *exp, t_env *env, int expand)
{
    int        i = 0;
    char    *result = ft_strdup("");

    while (exp[i])
    {
        if (exp[i] == '\'')
            result = handle_single_quote(exp, &i, result);
        else if (exp[i] == '"')
            result = handle_double_quote(exp, &i, result, env, expand);
        else if (exp[i] == '$' && expand && exp[i+1] &&  exp[i+1] != ' ' && exp[i+1] != '\t' && exp[i+1] != ',')
        {
            
            i++;
            if(exp[i] == '$')
            {
                result = str_append(result, ft_itoa((int)getpid()));
                i++;
            }
            else if(exp[i] == '?')
            {
                result = str_append(result, ft_itoa(env->exit_status));
                i++;
            }
            else
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

void    expand_rm_quotes(t_tokenn *t, t_env *env)
{
    t_tokenn    *tmp = t;
    t_tokenn    *prev = NULL;

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