/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:37:17 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/28 17:36:10 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	**gc_list(void)
{
	static t_gc	*head;

	return (&head);
}

t_gc	*gc_create_node(void *ptr)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (perror("malloc"), NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	gc_add_node(t_gc *new_node)
{
	t_gc	**head;
	t_gc	*temp;

	head = gc_list();
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

void	gc_free_all(void)
{
	t_gc	**head;
	t_gc	*current;
	t_gc	*next;

	head = gc_list();
	current = *head;
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
