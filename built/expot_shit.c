#include "../minishell.h"

void export_in_export(t_env **env, char *key, char *value)
{
	t_env	*new;

    new = gar_coll(sizeof(t_env), 'a');
    new->key = ft_strdup(key);
    new->value = value;
    new->next = *env;
    *env = new;
}

void null_value(t_env **env, char *arg)
{
	char	*key;
	char	*value;

	key = ft_strdup(arg);
	value = NULL;
	export_in_export(env, key, value);
}