#include "../minishell.h"

//delete this fonction

// void exit_value(t_env **env, int n)
// {
//     char *value;

//     value = ft_itoa(n);
//     export_in_env(env, "?", value);
//     free(value);
// }

void change_env_value(t_env **env, char *key, char *new_value)
{
    t_env *tmp;

    tmp = *env;
    while (tmp)
    {
        if (!ft_strcmp(key, tmp->key))
        {
            free(tmp->value);
            tmp->value = ft_strdup(new_value);
            return ;
        }
        tmp = tmp->next;
    }
}