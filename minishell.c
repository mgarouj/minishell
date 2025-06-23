/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 21:43:56 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_exitval = NULL;

int	main(int ac, char **av, char **env)
{
	t_env	*l;

	(void)ac;
	(void)av;
	handle_in();
	l = init_env_list(env);
	main_loop(l);
	return (0);
}