/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:06:16 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/18 15:39:52 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_fds **fds)
{
	t_fds	*tmp;

	if (!fds)
		return ;
	while (*fds)
	{
		close((*fds)->fd);
		tmp = *fds;
		*fds = (*fds)->next;
		free(tmp);
	}
}

void	fd_collec(int fd, int mode)
{
	t_fds			*new_fd;
	static t_fds	*fds;

	if (!mode)
	{
		close_fds(&fds);
		return ;
	}
	else if (mode && fd > 2)
	{
		new_fd = malloc(sizeof(t_fds));
		if (!new_fd)
		{
			close_fds(&fds);
			return ;
		}
		new_fd->fd = fd;
		new_fd->next = fds;
		fds = new_fd;
	}
}
