/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:44 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/15 17:23:30 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>     
# include <unistd.h>     
# include <stddef.h>     
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <wait.h>


enum token
{
	EXP,
	PIPE,
	REDIRECTION_IN, // <
	REDIRECTION_OUT, // >
	REDIRECTION_AP, // >>
	HEREDOC, // <<
};


typedef struct s_tokenn
{
	enum token	type;
	char			*value;
	struct s_tokenn	*next;
}	t_tokenn;


typedef struct s_env
{
	char *key;
	char *value;
	int	exit_status;
	struct s_env *next;
}	t_env;


typedef struct s_execution
{
	pid_t				pid;
	bool				is_builtin;
	char				*full_path;
	int pipe_fd[2];	
	bool				is_last;
	// bool 				is_first;

	char				**cmd;
	int					in_file;
	int					out_file;
	char				**env;
	char				*path;
	struct s_execution	*next;
}	t_execution;


typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_fds {
    int             fd;
    struct s_fds *next;
} t_fds;

// Parsing
int			parssing(char *line); 
t_tokenn	*tokenize(char *line);
void		handel_env(char *s, t_env **env);
void expand_rm_quotes(t_tokenn *t,t_env *l);
int split_cmd(t_tokenn *token,t_execution **exec);
void signal_handler(void);


//gc

void fd_collec(int fd, int mode);
void	*gar_coll(int size, char flag);

// Utils

char *ft_strchr(char *s, int c);
char *ft_strcat(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
int	find_dquote(char *line, int *i);
char	*ft_strdup(char *s);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*sub_str(char *s, int size);
void ft_putstr_fd(char *s,int fd);
char		*ft_strtrim(char *s, int size);
char		*ft_strndup(char *s, int n);
void print_err(char *str);
int ft_strlen(char *str);
char	*ft_substr(char *s, unsigned int start, int len);

// execution 

char	*ft_itoa(int n);
int	ft_atoi(const char *str);
int	ft_lstsize(t_env *lst);
char	*ft_strnstr(char *haystack, char *needle, int len);
char	*ft_strjoin(char *s1, char *s2);
int	ft_lstsize_cmd_list(t_execution *cmd_list);
int	ft_isalnum(int c);
pid_t ft_fork(const char *msg);
int	ft_isalpha(int c);
void	ft_3putstr(char *s1, char *s2, char *s3, char *s4);


//env 
char	*get_env_value(char *key, t_env *env);
void change_env_value(t_env **env, char *key, char *new_value);
t_env *find_var(t_env *env, char *key);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env *env_to_list(char **env);
char 	**ft_envsplit(char *env, char c);

// builtins 

void export_in_env(t_env **env, char *key, char *value);
int ft_cd(char **arg, t_env *env);
int ft_echo(char **arg);
int ft_export(char **args, t_env **env);
void export_plus_equal(t_env **env, char *arg);
void normal_export(t_env **env, char *arg);
int ft_unset(char **arg, t_env **env);
int ft_env(char **arg, t_env **env);
int ft_exit(char **arg, int exit_status);
int ft_pwd(t_env **env);
char *ft_strjoin_3(char *s1, char *s2);

//exec

void execute_cmd(t_execution **cmd_list, t_env **list_env);
void init_cmd(t_execution **cmd_list, int n_cmds);
void change_in_out(t_execution *cmd);
void restore_std(int in, int out);
char	*find_path(t_execution *cmd, t_env **env);
void execute_one_builtin(t_execution *cmd, t_env **env);
void execute_execve_cmd(t_execution *cmd, t_env **env);
int execute_builtins(t_execution *cmd, t_env **env);



// pipe fonction
void execute_pipe_cmd(t_execution **list_cmd, t_env **env, int n_cmds);
void	set_exit_status(t_env **env, int exit_status);




#endif // MINISHELL_H


