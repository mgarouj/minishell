#include "../minishell.h"

t_env *find_var(t_env *env, char *key)
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

void export_in_env(t_env **env, char *key, char *value)
{
    t_env *exist;
    t_env *new;

    exist = find_var(*env, key);
    if (!exist)
    {
        // new = malloc(sizeof(t_env));
        new = gar_coll(sizeof(t_env), 'a');
        // if (!new)
        //     return ;
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