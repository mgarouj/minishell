/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_one_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:44:34 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/24 13:50:46 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**change_envlist_to_envchar(t_env *env)
{
	t_env	*tmp;
	char	**env_array;
	char	*joined;
	int		i;
	int		size;

	tmp = env;
	size = ft_lstsize(env);
	env_array = gar_coll(sizeof(char *) * (size + 1), 'a');
	if (!env_array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			joined = ft_strjoin_3(tmp->key, tmp->value);
			env_array[i++] = joined;
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
