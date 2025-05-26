/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:50:45 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/26 16:16:21 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(t_env **env, char *key, char *new_value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->value = NULL;
			tmp->value = ft_strdup(new_value);
			return ;
		}
		tmp = tmp->next;
	}
}
