/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:56:57 by mgarouj           #+#    #+#             */
/*   Updated: 2025/07/02 15:14:10 by fbelkass         ###   ########.fr       */
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

void	export_in_env(t_env **env, char *key, char *value)
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
		new->next = *env;
		*env = new;
	}
}
