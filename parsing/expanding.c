/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:35:36 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/18 17:17:27 by fbelkass         ###   ########.fr       */
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

void replace(char **exp, char *var_name, t_env *l)
{
    t_env *tmp = l;
    char *new_value = NULL;
    char *new_exp;
    char *var_pos;
    int prefix_len;
    int var_len;

    while (tmp)
    {
        if (ft_strcmp(var_name, tmp->key) == 0)
        {
            new_value = tmp->value;
            break;
        }
        tmp = tmp->next;
    }

    if (new_value)
    {
        var_pos = ft_strstr(*exp, "$");
        if (!var_pos)
            return;

        prefix_len = var_pos - *exp;
        var_len = ft_strlen(var_name);

        // Allocate enough space: original length - $VAR + new_value + null
        new_exp = malloc(ft_strlen(*exp) - var_len + ft_strlen(new_value));
        if (!new_exp)
            return;

        ft_strlcpy(new_exp, *exp, prefix_len + 1);
        ft_strlcat(new_exp, new_value, ft_strlen(new_exp) + ft_strlen(new_value) + 1);
        ft_strlcat(new_exp, var_pos + 1 + var_len, ft_strlen(new_exp) + ft_strlen(var_pos + 1 + var_len) + 1);

        free(*exp);
        *exp = new_exp;
    }
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

// char *handel_afterd(char *exp, t_env *l)
// {
//     int i = 0;
//     int start;
//     char *var_name;

//     while (exp[i])
//     {
//         if(exp[i] == '"')
//         {   
//             i++;
//             if(!find_dquote(exp + i))
//             {
//                 print_err("error");
//                 return(NULL);
//             }
//             if (exp[i] == '$')
//             {
//                 i++;
//                 start = i;
//                 while (exp[i] && exp[i] != ' ' && exp[i] != '\t')
//                     i++;
//                 var_name = sub_str(exp + start, i - start);
//                 if (!var_name)
//                     return (NULL);

//                 if (in_env(var_name, l))
//                     replace(&exp, var_name, l);
//                 free(var_name);
//             }
//             if(exp[i] == '"')
//                 break;
//         }
//         else
//             i++;
//     }
//     while(exp[i])
//     {
        
//     }
//     return (exp);
// }
char *str_append(char *s1, const char *s2)
{
    char *new_str;
    size_t len = strlen(s1) + strlen(s2) + 1;

    new_str = malloc(len);
    if (!new_str)
        return NULL;
    strcpy(new_str, s1);
    strcat(new_str, s2);
    free(s1);
    return new_str;
}

char *str_append_char(char *s, char c)
{
    size_t len = strlen(s);
    char *new_str = malloc(len + 2);
    if (!new_str)
        return NULL;
    strcpy(new_str, s);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    free(s);
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

// char *handel_afterd(char *exp, t_env *env)
// {
//     int i = 0;
//     int start;
//     char *result = malloc(1);
//     char *var_name;
//     char *var_value;
//     int in_squote = 0, in_dquote = 0;

//     if (!result)
//         return NULL;
//     result[0] = '\0';

//     while (exp[i])
//     {
//         // if (exp[i] == '\'' && !in_dquote)
//         // {
//         //     in_squote = !in_squote;
//         //     i++;
//         // }
//         if (exp[i] == '\'' && !in_dquote)
//         {
//             in_squote = !in_squote;
//             i++; // skip the opening quote
//             while (exp[i] && exp[i] != '\'')
//             {
//                 result = str_append_char(result, exp[i]); // copy literally
//                 i++;
//             }
//             i++; // skip the closing quote
//         }

//         else if (exp[i] == '"' && !in_squote)
//         {
//             in_dquote = !in_dquote;
//             i++;
//         }
//         else if (exp[i] == '$' && !in_squote) // allow expansion only outside single quotes
//         {
//             i++;
//             start = i;
//             while (exp[i] && exp[i] != ' ' && exp[i] != '\t' &&
//                    exp[i] != '"' && exp[i] != '\'' && exp[i] != '$')
//                 i++;

//             var_name = sub_str(exp + start, i - start);
//             if (!var_name)
//                 return NULL;

//             var_value = get_env_value(var_name, env);
//             if (var_value)
//                 result = str_append(result, var_value);

//             free(var_name);
//         }
//         else
//         {
//             result = str_append_char(result, exp[i]);
//             i++;
//         }
//     }
//     return result;
// }

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

            free(var_name);
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
