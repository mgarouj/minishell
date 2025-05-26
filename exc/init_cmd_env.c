/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:42:58 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/26 11:04:29 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_env_cmd(t_env *env, t_execution **cmd)
{
    int		size;
	char	**str_env;
	int		j;
    t_execution *tmp_cmd;

	j = 0;
    tmp_cmd = *cmd;
	size = ft_lstsize(env);
	str_env = gar_coll(sizeof(char *) * (size + 1), 'a');
	while (j < size)
	{
		if (env->value)
			str_env[j] = ft_strjoin_3(env->key, env->value);
		else
			str_env[j] = ft_strdup(env->key);
		j++;
		env = env->next;
	}
    str_env[size] = NULL;
    while (tmp_cmd)
    {
        tmp_cmd->env = str_env;
        tmp_cmd = tmp_cmd->next;
    }
}
