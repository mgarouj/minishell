/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:34:10 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/01 16:13:44 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_heredoc(t_execution *exec, char *delimiter)
{
	int		fd[2];
	char	*line;

	if (!delimiter)
		return (0);
	if (pipe(fd) == -1)
	{
		print_err("heredoc error");
		return (0);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_err("heredoc input error");
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	if (exec->in_file != 0)
		close(exec->in_file);
	exec->in_file = fd[0];
    return(1);
}

char	*get_and_remove_delimiter(char **str)
{
	char	*delimiter;
	int		i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t')
		i++;
	delimiter = sub_str(*str, i);
	if ((*str)[i])
	{
		while ((*str)[i] == ' ' || (*str)[i] == '\t')
			i++;
		if ((*str)[i])
			*str = ft_strdup(*str + i);
		else
			*str = NULL;
	}
	else
		*str = NULL;
	return (delimiter);
}

int	heredoc(t_tokenn *token, t_execution *exec)
{
	t_tokenn	*tmp;
	// t_tokenn	*to_delete;
	char		*del;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next && tmp->next->type == EXP)
		{
			del = get_and_remove_delimiter(&tmp->next->value);
			if(!handel_heredoc(exec, del))
                return(0);
			// If after handling, the value is NULL, we delete the node
			if (tmp->next->value == NULL)
			{
				// to_delete = tmp->next;
				tmp->next = tmp->next->next;
				// free(to_delete);
			}
		}
		tmp = tmp->next;
	}
    return(1);
}
