#include "../minishell.h"

void normal_export(t_env **env, char *arg)
{
    int i;
    char *key;
    char *value;

    i = 0;
    while (arg[i] && !(arg[i] == '='))
        i++;
    key = ft_substr(arg, 0, i);
    value = ft_strdup(arg + i + 1);
    export_in_env(env, key, value);
    free(key);
    free(value);
}


void export_plus_equal(t_env **env, char *arg)
{
    char *key;
    char *value;
    char *old_value;
    char *new_value;
    t_env *exist;
    int i;
    
    i = 0;
    while (arg[i] && !(arg[i] == '+' && arg[i + 1] == '='))
        i++;
    key = ft_substr(arg, 0, i);
    value = ft_strdup(arg + i + 2);
    exist = find_var(*env, key);
    if (exist && exist->value)
    {
        old_value = exist->value;
        new_value = ft_strjoin(old_value, value);
        free(exist->value);
        exist->value = new_value;
    }
    else
        export_in_env(env, key, value);
    free(key);
    free(value);
}
