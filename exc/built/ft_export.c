#include "../minishell.h"

char *ft_strjoin_3(char *s1, char *s2)
{
    char *join3;
    int i;
    int j;

    if (!s2)
        return (ft_strdup(s1));
    join3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
    i = 0;
    while (s1[i])
    {
       join3[i] = s1[i];
       i++;
    }
    join3[i++] = '=';
    j = 0;
    while (s2[j])
    {
       join3[i] = s2[j];
       j++;
       i++;
    }
    join3[i] = '\0';
    return (join3);
}

void ft_sort_env(char **sort_env, int size)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (sort_env[i])
    {
        j = 0;
        while (sort_env[j + 1])
        {
            if (ft_strcmp(sort_env[j], sort_env[j + 1]) > 0)
            {
                tmp = sort_env[j];
                sort_env[j] = sort_env[j + 1];
                sort_env[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
} 

int print_sorted_env(t_envrmt *env)
{
    int size;
    char **sort_env;
    int j;

    j = 0;
    size = ft_lstsize(env);
    sort_env = malloc(sizeof(char *) * (size + 1));
    while (j < size)
    {
        if (env->value)
            sort_env[j] = ft_strjoin_3(env->key, env->value);
        else
            sort_env[j] = ft_strdup(env->key);
        j++;
        env = env->next;
    }
    ft_sort_env(sort_env, size);
    j = 0;
    while (sort_env[j])
        printf("declare -x %s\n", sort_env[j++]);
    j = 0;
    while (sort_env[j])
        free(sort_env[j++]);
    free(sort_env);
    return (0);
}

int ft_export(char **args, t_envrmt **env)
{

    // export -> print -> sorted env
    if (!args[1])
    {
        return (print_sorted_env(*env));
    }
    else if (ft_strnstr(args[1], "+=", ft_strlen(args[1])))
    {
        export_plus_equal(env, args[1]);
    }
    else
    {
        normal_export(env, args[1]);
    }
    return (0);
}
