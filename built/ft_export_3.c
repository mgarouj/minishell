/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:18:27 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/02 15:15:57 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_key(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
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
	if (!check_env_key(arg, *env))
		export_in_export(env, ft_strdup(arg), NULL);
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
