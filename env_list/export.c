/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:56:57 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/22 17:26:07 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_var(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	export_in_env(t_env **env, char *key, char *value, int printed)
{
	t_env	*exist;
	t_env	*new;

	exist = find_var(*env, key);
	if (exist)
		exist->value = ft_strdup(value);
	else
	{
		new = gar_coll(sizeof(t_env), 'a');
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->printed = printed;
		new->next = *env;
		*env = new;
	}
}
