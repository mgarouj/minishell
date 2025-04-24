#include "../minishell.h"

t_envrmt *find_var(t_envrmt *env, char *key)
{
    while (env)
    {
        if (!ft_strcmp(env->key, key))
            return (env);
        env = env->next;
    }
    return (NULL);
}

// this fonction find varibale in env and change the value of this variable

void export_in_env(t_envrmt **env, char *key, char *value)
{
    t_envrmt *exist;
    t_envrmt *new;

    exist = find_var(*env, key);
    if (!exist)
    {
        new = malloc(sizeof(t_envrmt));
        if (!new)
            return ;
        new->key = ft_strdup(key);
        new->value = ft_strdup(value);
        new->next = *env;
        *env = new;
    }
    else
    {
        free(exist->value);
        exist->value = ft_strdup(value);
    }
}