/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:37:17 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/21 14:52:54 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_gc	*head;

static t_gc	**gc_list(void)
{
	return (&head);
}

static t_gc	*gc_create_node(void *ptr)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (perror("malloc"), NULL);
	new_node->ptr = ptr;
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
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	*gar_coll(int size, char flag)
{
	void	*ptr;
	t_gc	*node;

	if (flag == 'f')
		return (gc_free_all(), NULL);
	ptr = malloc(size);
	if (!ptr)
		return (perror("malloc"), exit(1), NULL);
	node = gc_create_node(ptr);
	if (!node)
		return (free(ptr), NULL);
	gc_add_node(node);
	return (ptr);
}
