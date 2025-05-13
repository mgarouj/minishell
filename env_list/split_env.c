#include "../minishell.h"

char **ft_envsplit(char *env, char c)
{
    int     i;
    char    **str;

    i = 0;
    str = malloc(sizeof(char *) * 3);
    if (!str)
        return (NULL);
    while (env[i] && env[i] != c)
        i++;
    str[0] = ft_substr(env, 0, i);
    if (env[i]) 
        str[1] = ft_substr(env, i + 1, ft_strlen(env) - i - 1);
    else
        str[1] = ft_strdup("");
    str[2] = NULL;
    return (str);
}