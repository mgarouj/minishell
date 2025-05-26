/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:05:24 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/23 16:05:57 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_keys(char *key, t_env **env)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (prev == NULL)
				*env = cur->next;
			else
				prev->next = cur->next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	is_valid_key(char *arg)
{
	int	i;

	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i])
	{
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **arg, t_env **env)
{
	int	i;
	int	status;

	status = 0;
	if (!arg[1])
		return (status);
	i = 1;
	while (arg[i])
	{
		if (!is_valid_key(arg[i]))
		{
			printf("minishell: unset: `%s`: not a valid identifier\n", arg[i]);
			status = 1;
		}
		else
			remove_keys(arg[i], env);
		i++;
	}
	return (status);
}
