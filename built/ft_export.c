/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:40:27 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/29 18:35:42 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_3sort(char *s1, char *s2)
{
	char	*join3;
	int		i;
	int		j;

	if (!s2)
		return (ft_strdup(s1));
	join3 = gar_coll(ft_strlen(s1) + ft_strlen(s2) + 2 + 2, 'a');
	i = 0;
	while (s1[i])
	{
		join3[i] = s1[i];
		i++;
	}
	join3[i++] = '=';
	join3[i++] = '\"';
	j = 0;
	while (s2[j])
	{
		join3[i] = s2[j];
		j++;
		i++;
	}
	join3[i++] = '\"';
	join3[i] = '\0';
	return (join3);
}

void	ft_sort_env(char **sort_env, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (sort_env[j + 1])
		{
			if (ft_strcmp(sort_env[j], sort_env[j + 1]) > 0)
			{
				tmp = sort_env[j];
				sort_env[j] = sort_env[j + 1];
				sort_env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_env *env)
{
	int		size;
	char	**sort_env;
	int		j;

	j = 0;
	size = ft_lstsize(env);
	sort_env = gar_coll(sizeof(char *) * (size + 1), 'a');
	while (env)
	{
		if (env->printed)
		{
			if (env->value)
				sort_env[j] = ft_strjoin_3sort(env->key, env->value);
			else
				sort_env[j] = ft_strdup(env->key);
			j++;
		}
		env = env->next;
	}
	sort_env[j] = NULL;
	ft_sort_env(sort_env, j);
	j = 0;
	while (sort_env[j])
		ft_3putstr("declare -x ", sort_env[j++], "\n", NULL);
	return (0);
}

void	print_export(char **args, int i)
{
	ft_3putstr_err("minishell: export: ", args[i], ": not a valid identifier\n",
		NULL);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[1])
		return (print_sorted_env(*env));
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_export(args, i);
			exit_status = 1;
			i++;
			continue ;
		}
		if (ft_strnstr(args[i], "+=", ft_strlen(args[i])))
			export_plus_equal(env, args[i], 0);
		else if (ft_strchr(args[i], '='))
			normal_export(env, args[i]);
		else
			null_value(env, args[i]);
		i++;
	}
	return (exit_status);
}
