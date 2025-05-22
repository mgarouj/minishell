/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:24:34 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/22 16:47:57 by fbelkass         ###   ########.fr       */
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

char    *expand_variable(char *exp, int *i, t_env *env, char *result,t_tokenn **tmp)
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
    {
        (*tmp)->expanded = 1;
        result = str_append(result, var_value);
    }
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

char    *handle_double_quote(char *exp, int *i, char *result, t_env *env, int expand,t_tokenn **tmp)
{
    (*i)++;
    while (exp[*i] && exp[*i] != '"')
    {
        if (exp[*i] == '$' && expand && exp[(*i) + 1]!='"' && exp[(*i) + 1] != ' ' && exp[(*i) + 1] != '\t' && exp[(*i) + 1] != ',')
        {
            (*i)++;
            result = expand_variable(exp, i, env, result,tmp);
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

char    *handel_afterd(char *exp, t_env *env, int expand,t_tokenn **tmp)
{
    int        i = 0;
    char    *result = ft_strdup("");

    while (exp[i])
    {
        if (exp[i] == '\'')
            result = handle_single_quote(exp, &i, result);
        else if (exp[i] == '"')
        {
            (*tmp)->quoted=1;
            result = handle_double_quote(exp, &i, result, env, expand,tmp);
        }
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
             result = expand_variable(exp, &i, env, result,tmp);
        }
        else
        {
            result = str_append_char(result, exp[i]);
            i++;
        }
    }
    return (result);
}

void    retoken(t_tokenn *token)
{
    char        **split;
    t_tokenn    *new_node;
    t_tokenn    *t;
    int         i;

    split = ft_split_whitespace(token->value); // Split on space and tab
    if (!split || !split[0])
        return;

    free(token->value); // Or let GC handle this if gar_coll used
    token->value = ft_strdup(split[0]); // Replace with first word
    token->expanded = 0; // Reset flag (can also keep it set if needed)
    
    t = token;
    i = 1;
    while (split[i])
    {
        new_node = gar_coll(sizeof(t_tokenn), 'a');
        if (!new_node)
            return;

        new_node->type = EXP;
        new_node->value = ft_strdup(split[i]);
        new_node->expanded = 0;
        new_node->next = t->next;
        t->next = new_node;
        t = new_node;
        i++;
    }
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
            tmp->value = handel_afterd(tmp->value, env, expand,&tmp);
        }
        if(tmp->expanded && !(tmp->quoted) && (ft_strchr(tmp->value,' ') || ft_strchr(tmp->value,'\t')))
            retoken(tmp);
        prev = tmp;
        tmp = tmp->next;
    }
}