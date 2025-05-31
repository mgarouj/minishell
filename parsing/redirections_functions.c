/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:01 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/31 16:53:09 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_redin(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdin") == 0)
		exec->in_file = STDIN_FILENO;
	else
	{
	fd = open(filename, O_RDONLY);
	fd_collec(fd, 1);
	if (fd == -1)
	{
		fd_collec(0, 0);
		return (0);
	}
	if (exec->in_file != 0)
		close(exec->in_file);
	exec->in_file = fd;
	}
	return (1);
}

int	handel_reout(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdout") == 0)
		exec->out_file = STDOUT_FILENO;
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd_collec(fd, 1);
		if (fd == -1)
		{
			fd_collec(0, 0);
			return (0);
		}
		if (exec->out_file != 1)
			close(exec->out_file);
		exec->out_file = fd;
	}
	return (1);
}

int	handel_redappend(char *filename, t_execution *exec)
{
	int	fd;

	if (ft_strcmp(filename, "/dev/stdout") == 0)
		exec->out_file = STDOUT_FILENO;
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	}
	return (1);
}

// char * expand_in_heredoc(char *line,int *i,t_env *env)
// {
// 	int start;
// 	char *new_va;

// 	start = *i;
// 	while(line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != ',' &&
// 			line[*i] != ';' && line[*i] != '$' && line[*i] != '\''
				//&& line[*i] != '"')
// 				(*i)++;
// 	new_va = get_env_value(sub_str(line,(*i) - start),env);
// 	if(new_va)
// 		line = str_append(line,new_va);
// 	return(line);
// }

// char * replace(char *line,t_env *env)
// {
// 	int i;
// 	char *r;

// 	i = 0;
// 	while(line[i] != '$')
// 		i++;
// 	while(line[i] && is_whitespace(line[i]))
// 		i++;
// 	if(!line[i + 1])
// 		return(ft_strdup(line));
// 	r = ft_strdup("");
// 		i = 0;
// 	if(line[i] == '$')
// 	{
// 		i++;
// 		r = expand_in_heredoc(line,&i,env);
// 	}
// 	else
// 	{
// 		r = str_append_char(line,line[i]);
// 		i++;
// 	}
// 	return(r);
// }

char	*replace(char *line, t_env *env)
{
	int		i;
	int		start;
	char	*result;
	char	*tmp;
	char	*value;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > start)
			{
				tmp = sub_str(line + start, i - start);
				result = str_append(result, tmp);
			}
			i++;
			start = i;
			if (!line[i] || !(ft_isalpha(line[i]) || line[i] == '_'))
			{
				result = str_append_char(result, '$');
				start = i;
				continue ;
			}
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
				i++;
			tmp = sub_str(line + start, i - start);
			value = get_env_value(tmp, env);
			if (value)
				result = str_append(result, value);
			start = i;
		}
		else
		{
			i++;
		}
	}
	if (i > start)
	{
		tmp = sub_str(line + start, i - start);
		result = str_append(result, tmp);
	}
	return (result);
}

int	process_heredoc_input(int pipe_fd, char *delimiter, t_env *env)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_err("heredoc input error");
			return (0);
		}
		if (ft_strchr(line, '$'))
		{
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$') && (ft_strchr(delimiter, '"')
				|| ft_strchr(delimiter, '\'')))
		{
			tmp = replace(line, env);
			write(pipe_fd, tmp, ft_strlen(tmp));
			write(pipe_fd, "\n", 1);
			free(line);
		}
		else
		{
			write(pipe_fd, line, ft_strlen(line));
			write(pipe_fd, "\n", 1);
			free(line);
		}
	}
	return (1);
}

int	handle_heredoc(char *delimiter, t_execution *exec, t_env *env)
{
	int	fd[2];

	if (!delimiter)
		return (0);
	if (pipe(fd) == -1)
	{
		print_err("heredoc error");
		return (0);
	}
	if (!process_heredoc_input(fd[1], delimiter, env))
	{
		close(fd[1]);
		close(fd[0]);
		return (0);
	}
	close(fd[1]);
	if (exec->in_file != 0)
		close(exec->in_file);
	exec->in_file = fd[0];
	return (1);
}
