#include "../minishell.h"

// this fonction searching for target in env if target -> env return (env.value) if terget !! env return ("")

char *get_env(t_env *env, char *target)
{
    t_env *tmp;

    if (!target || !*target)
        return (NULL);
    tmp = env;
    while (tmp)
    {
        if (!target || !tmp->key)
            break;
        if (!ft_strcmp(target, tmp->key))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void oldpwd_check(char **s)
{
    if (!ft_strcmp(s[0], "OLDPWD"))
    {
        free(s[1]);
        s[1] = ft_strdup("");
    }
}

t_env *lstnew_env(char *key, char *value)
{
    t_env *lst;

    lst = malloc(sizeof(t_env));
    if (!lst)
        return (NULL);
    lst->key = key;
    lst->value = value;
    lst->next = NULL;
    return (lst);
}

t_env *env_to_list(char **env)
{
    char **split_str;
    t_env *envp;
    t_env *tmp;
    int i;

    i = 0;
    tmp = NULL;
    envp = NULL;
    while (env[i])
    {
        split_str = ft_envsplit(env[i], '=');
        oldpwd_check(split_str);
        tmp = lstnew_env(split_str[0], split_str[1]);
        ft_lstadd_back(&envp, tmp);
        free(split_str);
        i++;
    }
    return (envp);
}
