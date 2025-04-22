/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:37:17 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/22 13:50:29 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_gc	*head;
static t_fd_gc *fds ;

static t_gc	**gc_list(void)
{
	return (&head);
}

static t_gc	*gc_create_node(void *ptr, bool is_free)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (perror("malloc"), NULL);
	new_node->ptr = ptr;
	new_node->is_free = is_free;
	new_node->next = NULL;
	return (new_node);
}

static void	gc_add_node(t_gc *new_node)
{
	t_gc	**head = gc_list();
	t_gc	*temp;

	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

static void	gc_free_all(void)
{
	t_gc	**head = gc_list();
	t_gc	*current = *head;
	t_gc	*next;

	while (current)
	{
		next = current->next;
		if (current->is_free && current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	*gar_coll(size_t size, int flag, bool is_free)
{
	void	*ptr;
	t_gc	*node;

	if (flag == 'f')
		return (gc_free_all(), NULL);
	ptr = malloc(size);
	if (!ptr)
		return (perror("malloc"), exit(1), NULL);
	node = gc_create_node(ptr, is_free);
	if (!node)
		return (free(ptr), NULL);
	gc_add_node(node);
	return (ptr);
}


void close_fds(t_fd_gc **fds)
{
    t_fd_gc *tmp;

    if (!fds)
        return;

    while (*fds)
    {
        close((*fds)->fd);  // Optionally log error with perror()
        tmp = *fds;
        *fds = (*fds)->next;
        free(tmp);
    }
}

void fd_collec(int fd, int mode)
{
    t_fd_gc *new_fd;

    if (mode && fd > 2) // Avoid invalid or std fds
    {
        new_fd = malloc(sizeof(t_fd_gc));
        if (!new_fd)
        {
            close_fds(&fds);
            return;
        }
        new_fd->fd = fd;
        new_fd->next = fds;
        fds = new_fd;
    }
    else if (!mode)
        close_fds(&fds);
}
