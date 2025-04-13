/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:35:36 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/13 20:48:42 by fbelkass         ###   ########.fr       */
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

    // Find the variable in the environment list
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
        // Allocate memory for the new expression
        new_exp = malloc(ft_strlen(*exp) + ft_strlen(new_value) - ft_strlen(var_name) + 1);
        if (!new_exp)
            return;
        // Replace the $variable with its value in the string
        var_pos = ft_strstr(*exp, "$");
        prefix_len = var_pos - *exp;

        ft_strlcpy(new_exp, *exp, prefix_len + 1);
        ft_strlcat(new_exp, new_value, ft_strlen(new_exp) + ft_strlen(new_value) + 1);
        ft_strlcat(new_exp, var_pos + ft_strlen(var_name), ft_strlen(new_exp) + ft_strlen(var_pos + ft_strlen(var_name)) + 1);

        free(*exp);  // Free the old expression
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

char *handel_afterd(char *exp, t_env *l)
{
    int i = 0;
    int start;
    char *var_name;

    while (exp[i])
    {
        if (exp[i] == '$')
        {
            i++;
            start = i;
            while (exp[i] && exp[i] != ' ' && exp[i] != '\t')
                i++;

            var_name = sub_str(exp + start, i - start);
            if (!var_name)
                return (NULL);

            if (in_env(var_name, l))
                replace(&exp, var_name, l);

            free(var_name);
        }
        else
            i++;
    }
    return (exp);
}

int expanding(t_tokenn *t,t_env *l)
{
    t_tokenn *tmp;

    tmp = t;
    while (tmp)
    {
        if (tmp->type == EXP)
            tmp->value = handel_afterd(tmp->value, l);
        tmp = tmp->next;
    }
    
}