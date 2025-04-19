/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:35:36 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/19 16:30:47 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

int ft_find(char *s,char c)
{
    int i;

    i = 0;
    while(s[i])
    {
        if(s[i] == c)
            return(1);
        i++;
    }
    return(0);
}



int in_env(char *s,t_env *l)
{
    t_env *tmp;

    tmp = l;
    while(tmp)
    {
        if(ft_strcmp(s,tmp -> key))
            return(1);
        tmp = tmp -> next;
    }
    return(0);
}


char *str_append(char *s1,  char *s2)
{
    char *new_str;
    size_t len = ft_strlen(s1) + ft_strlen(s2) + 1;

    new_str = gar_coll(len,'a',1);
    if (!new_str)
        return NULL;
    ft_strcpy(new_str, s1);
    ft_strcat(new_str, s2);
    // free(s1);
    return new_str;
}

char *str_append_char(char *s, char c)
{
    size_t len = ft_strlen(s);
    char *new_str = gar_coll(len + 2,'a',1);
    if (!new_str)
        return NULL;
    ft_strcpy(new_str, s);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    // free(s);
    return new_str;
}

char *get_env_value(char *key, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}



char *handel_afterd(char *exp, t_env *env)
{
    int i = 0;
    char *result = ft_strdup("");
    int in_squote = 0, in_dquote = 0;

    while (exp[i])
    {
        if (exp[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++; // skip quote
            continue;
        }
        if (exp[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
            i++; // skip quote
            continue;
        }
        if (exp[i] == '$' && !in_squote)
        {
            i++;
            int start = i;
            while (exp[i] && exp[i] != ' ' && exp[i] != '\t' &&
                   exp[i] != '"' && exp[i] != '\'' && exp[i] != '$')
                i++;

            char *var_name = sub_str(exp + start, i - start);
            char *var_value = get_env_value(var_name, env);

            if (var_value)
                result = str_append(result, var_value);

            // free(var_name);
            continue;
        }

        result = str_append_char(result, exp[i]);
        i++;
    }

    return result;
}

void  expanding(t_tokenn *t,t_env *l)
{
    t_tokenn *tmp;

    tmp = t;
    while (tmp)
    {
        if (tmp->type == EXP)
        {
            tmp->value = handel_afterd(tmp->value, l);
        }
        
        tmp = tmp->next;
    }
}
