/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expot_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:18:27 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/20 22:58:07 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_key(char *key, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, key) == 0)
			return (env_tmp->key);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

void	export_in_export(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = gar_coll(sizeof(t_env), 'a');
	new->key = ft_strdup(key);
	new->value = value;
	new->next = *env;
	*env = new;
}

void	null_value(t_env **env, char *arg)
{
	char	*key;
	char	*value;

	key = ft_strdup(arg);
	value = NULL;
	if (!get_env_key(key, *env))
		export_in_export(env, key, value);
}

int	is_valid_identifier(const char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i] && s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
