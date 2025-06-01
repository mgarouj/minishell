/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:40:27 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/30 17:27:42 by fbelkass         ###   ########.fr       */
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
	while (j < size)
	{
		if (env->value)
			sort_env[j] = ft_strjoin_3sort(env->key, env->value);
		else
			sort_env[j] = ft_strdup(env->key);
		j++;
		env = env->next;
	}
	sort_env[size] = NULL;
	ft_sort_env(sort_env, size);
	j = 0;
	while (sort_env[j])
		ft_3putstr("declare -x ", sort_env[j++], "\n", NULL);
	j = 0;
	return (0);
}

void	print_msj(char **arg, int i, int start)
{
	int	p;
	int	flag;

	start = 2;
	while (start < i)
	{
		p = 0;
		flag = 0;
		while (arg[start][p])
		{
			if (!ft_lnum_export(arg[start][p]))
				flag = 1;
			p++;
		}
		if (flag)
		{
			ft_3putstr("minishell: export: ",
				arg[start], ": not a valid identifier\n", NULL);
		}
		start++;
	}
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (args[i])
		i++;
	if (i > 1)
		flag = handle_arg1(args[1]);
	if (i >= 2)
		print_msj(args, i, 2);
	if (flag)
		return (flag);
	if (!args[1])
		return (print_sorted_env(*env));
	else if (ft_strnstr(args[1], "+=", ft_strlen(args[1])))
		export_plus_equal(env, args[1], 0);
	else if (ft_strchr(args[1], '='))
		normal_export(env, args[1]);
	else 
		null_value(env, args[1]);
	return (0);
}
