/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:30 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/25 18:33:07 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(const char *msg)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(msg);
		gar_coll(0, 1);
		fd_collec(0, 0);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
