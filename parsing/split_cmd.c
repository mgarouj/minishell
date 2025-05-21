/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:09:09 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/21 15:14:40 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execution *creat_node()
{
	t_execution *exec;

	exec = gar_coll(sizeof(t_execution), 'a');
	exec->cmd = NULL;
	exec->in_file = 0;
	exec->out_file = 1;
	exec->next = NULL;
	return (exec);
}

void add_node_to_list(t_execution **exec, t_execution *node)
{
	t_execution *tmp;

	if (!*exec)
	{
		*exec = node;
		return;
	}
	tmp = *exec;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int append_to_cmd(char *exp, t_execution *exec)
{
	int i;
	char **new_cmd;
	int j;

	if (!exp || !exec)
		return (0);
	i = 0;
	if (exec->cmd)
	{
		while (exec->cmd[i])
			i++;
	}
	new_cmd = gar_coll(sizeof(char *) * (i + 2), 'a');
	if (!new_cmd)
		return (0);
	j = 0;
	if (exec->cmd)
	{
		while (j < i)
		{
			new_cmd[j] = exec->cmd[j];
			j++;
		}
	}
	new_cmd[j] = ft_strdup(exp);
	if (!new_cmd[j])
		return (0);
	new_cmd[j + 1] = NULL;
	exec->cmd = new_cmd;
	return (1);
}

int is_redirection(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">") ||
			!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

int handel_redin(char *filename, t_execution *exec)
{
	int fd = open(filename, O_RDONLY);
	fd_collec(fd, 1);
	if (fd == -1)
	{
		print_err("failed to open input file");
		fd_collec(0, 0);
		return (0);
	}
	if (exec->in_file != 0)
		close(exec->in_file);
	exec->in_file = fd;
	return (1);
}

int handel_reout(char *filename, t_execution *exec)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd_collec(fd, 1);
	if (fd == -1)
	{
		print_err("failed to open output file");
		fd_collec(0, 0);
		return (0);
	}
	if (exec->out_file != 1)
		close(exec->out_file);
	exec->out_file = fd;
	return (1);
}

int handel_redappend(char *filename, t_execution *exec)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	fd_collec(fd, 1);
	if (fd == -1)
	{
		print_err("failed to open file for append");
		fd_collec(0, 0);
		return (0);
	}
	if (exec->out_file != 1)
		close(exec->out_file);
	exec->out_file = fd;
	return (1);
}


int	handle_heredoc(char *delimiter,t_execution *exec)
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

int handel_redirections(t_tokenn *token, char *file_name, t_execution *exec)
{
	if (token->type == REDIRECTION_IN)
		return handel_redin(file_name, exec);
	else if (token->type == REDIRECTION_OUT)
		return handel_reout(file_name, exec);
	else if (token->type == REDIRECTION_AP)
		return handel_redappend(file_name, exec);
	else if (token->type == HEREDOC)
		return handle_heredoc(file_name, exec);
	return (0);
}

int split_cmd(t_tokenn *token,t_execution **exec_list)
{
	t_tokenn *tmp = token;
    t_execution *exec;
    
	while (tmp)
	{
		exec = creat_node();
		if (!exec)
			return (0);
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == EXP && tmp->value && tmp->value[0])
			{
				if (!append_to_cmd(tmp->value, exec))
					return (0);
			}
			else if (is_redirection(tmp->value))
			{
				if (!tmp->next || !handel_redirections(tmp, tmp->next->value, exec))
				{
					print_err("invalid redirection");
					return (0);
				}
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
		add_node_to_list(exec_list, exec);
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
	return (1);
}
