/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:01 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/01 22:25:21 by fbelkass         ###   ########.fr       */
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

char	*expand_variable_inheredoc(char *exp, int *i, char *result, t_env *env)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (exp[*i] && exp[*i] != ' ' && exp[*i] != '\t' && exp[*i] != '"'
		&& exp[*i] != '\'' && exp[*i] != '$' && exp[*i] != ','
		&& exp[*i] != ';' && exp[*i] != '.' && exp[*i] != '[' && exp[*i] != ']' && exp[*i] != '=' && exp[*i] != '%' && exp[*i] != '*')
		(*i)++;
	var_name = sub_str(exp + start, (*i) - start);
	var_value = get_env_value(var_name, env);
	if (var_value)
		result = str_append(result, var_value);
	return (result);
}

void	handel_specials_inheredoc(char **result, char *exp, t_env *env, int *i)
{
	(*i)++;
	if (exp[*i] == '$')
	{
		(*i)++;
	}
	else if (exp[*i] == '?')
	{
		*result = str_append(*result, ft_itoa(env->exit_status));
		(*i)++;
	}
	else if(is_num(exp[*i]))
	{
		(*i)++;
		while(exp[*i])
		{
			*result= str_append_char(*result,exp[*i]);
			(*i)++;
		}
	}
	else
		*result = expand_variable_inheredoc(exp, i, *result, env);
}

char	*handel_afterd_inherdoc(char *exp, t_env *env)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (exp[i])
	{
			if (exp[i] == '$' && exp[i + 1] && exp[i
					+ 1] != ' ' && exp[i + 1] != '\t' && exp[i + 1] != ',' && exp[i + 1] != ':' && exp[i + 1] != '=' && exp[i + 1] != '+')
				handel_specials_inheredoc(&result, exp, env, &i);
			else
			{
				result = str_append_char(result, exp[i]);
				i++;
			}
	}
		return (result);
}

int	heredoc(char *delimiter, int quotes, t_execution *exec, t_env *env)
{
	pid_t	pid;
	int		fd_write, fd_read;
	char	*line, *tmp;
	int		exit_status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal_handler(2);
		if (!access(".tmp_file", F_OK))
		unlink(".tmp_file");
		fd_write = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_write < 0){
			print_err("heredoc: failed to open for writing");
			exit(1);}
		while (1)
		{
			line = readline("> ");
			if(!line)
			{
				print_err("heredoc input error");
				exit (0);
			}
			if (!ft_strcmp(delimiter, line))
			{        
				free(line);
				break;
			}
			if (ft_strchr(line, '$') && !quotes)
			{
				tmp = handel_afterd_inherdoc(line, env);
				write(fd_write, tmp, ft_strlen(tmp));
				write(fd_write, "\n", 1);
				free(line);
			}
			else
			{
				write(fd_write, line, ft_strlen(line));
				write(fd_write, "\n", 1);
				free(line);
			}
			free(line);
		}
		close(fd_write);
		fd_read = open(".tmp_file", O_RDONLY);
		if (fd_read < 0){
			print_err("heredoc input error");
			exit(1);}
		unlink(".tmp_file");
		exec->in_file = fd_read;
		exit(0);
	}
	else
	{
			waitpid(pid, &exit_status, 0);
	signal_handler(1); // رجّع signals ديال prompt

	if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
	{
		write(1, "\n", 1);
		set_exit_status(&env, 130); // ⬅️ خاص ترجع 130 يدوياً
		return (0); // ⬅️ خاص توقف execution ديال heredoc
	}
	else if (WIFEXITED(exit_status))
		set_exit_status(&env, WEXITSTATUS(exit_status));
	}
	return (0);
}
