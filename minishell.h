/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:44 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/31 18:26:47 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_token
{
	EXP,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_AP,
	HEREDOC,
};

typedef struct s_tokenn
{
	enum e_token		type;
	char				*value;
	int	quotes;
	struct s_tokenn		*next;
}						t_tokenn;

typedef struct s_export
{
	char *key;
	char *value;
	int	flag_env;
	struct s_export *next;
}	t_export;

typedef struct s_env
{
	char *key;
	char *value;
	int	exit_status;
	char	*pwd;
	t_export 	*export;
	struct s_env *next;
}	t_env;

typedef struct s_expand_data
{
	t_env				*env;
	int					expanded;
	int					sh_expand;
	int					quoted;

}						t_expand_data;

typedef struct s_execution
{
	pid_t				pid;
	bool				is_builtin;
	int					pipe_fd[2];
	bool				is_last;

	char				**cmd;
	int					in_file;
	int					out_file;
	char				**env;
	char				*path;
	struct s_execution	*next;
}						t_execution;

typedef struct s_gc
{
	void				*ptr;
	struct s_gc			*next;
}						t_gc;

typedef struct s_fds
{
	int					fd;
	struct s_fds		*next;
}						t_fds;

// Parsing
int						parssing(char *line);
t_tokenn				*tokenize(char *line);
void					handel_env(char *s, t_env **env);
int					expand_rm_quotes(t_tokenn *t, t_env *l);
int						split_cmd(t_tokenn *token, t_execution **exec,t_env *env);
void					signal_handler(int f);
void					retoken(t_tokenn *token);
// gc

void					fd_collec(int fd, int mode);
void					*gar_coll(int size, char flag);

// Utils

char					*ft_strchr(char *s, int c);
char					*ft_strcat(char *dest, char *src);
char					*ft_strcpy(char *dest, char *src);
int						find_dquote(char *line, int *i);
char					*ft_strdup(char *s);
char					**ft_split(char *s, char c);
int						ft_strcmp(char *s1, char *s2);
char					*sub_str(char *s, int size);
void					ft_putstr_fd(char *s, int fd);
char					*ft_strtrim(char *s, int size);
char					*ft_strndup(char *s, int n);
void					print_err(char *str);
int						ft_strlen(char *str);
char					*ft_substr(char *s, unsigned int start, int len);
char					**ft_split_whitespace(char *s);
int						is_whitespace(char c);
int						find_dquote(char *line, int *i);
int						find_squote(char *line, int *i);
int						is_valid_redir_count(char *line, int *i, char redir);
int						is_valid_redir_target(char *line, int *i);
int	is_num(char c);
// token
t_tokenn				*create_token(enum e_token type, char *value,int quotes);
void					add_token(t_tokenn **head, t_tokenn *new_token);
int						is_operator(char c);
void					skip_whitespace(char *line, int *i);

// expanding

char					*str_append(char *s1, char *s2);
char					*str_append_char(char *s, char c);
char					*get_env_value(char *key, t_env *env);
char					*expand_variable(char *exp, int *i, char *result,
							t_expand_data *data);
char					*handle_single_quote(char *exp, int *i, char *result);

// execution

char					*ft_itoa(int n);
int						ft_atoi(const char *str);
int						ft_lstsize(t_env *lst);
char					*ft_strnstr(char *haystack, char *needle, int len);
char					*ft_strjoin(char *s1, char *s2);
int						ft_lstsize_cmd_list(t_execution *cmd_list);
int						ft_isalnum(int c);
pid_t					ft_fork(const char *msg);
int						ft_isalpha(int c);
void					ft_3putstr(char *s1, char *s2, char *s3, char *s4);
int						handle_arg1(char *v);
void    				init_env_cmd(t_env *env, t_execution **cmd);

// splitcmd
t_execution				*creat_node(void);
void					add_node_to_list(t_execution **exec, t_execution *node);
int						is_redirection(char *s);
int						calculate_required_size(char *exp, t_execution *exec);
int						copy_and_append_cmd(char **new_cmd, t_execution *exec,
							char *exp);

// red
int						handel_redin(char *filename, t_execution *exec);
int						handel_reout(char *filename, t_execution *exec);
int						handel_redappend(char *filename, t_execution *exec);
int						process_heredoc_input(int pipe_fd, char *delimiter,t_env *env);
int						handle_heredoc(char *delimiter, t_execution *exec,t_env *env);

// env
char					*get_env_value(char *key, t_env *env);
void					change_env_value(t_env **env, char *key,
							char *new_value);
t_env					*find_var(t_env *env, char *key);
void					ft_lstadd_back(t_env **lst, t_env *new);
t_env					*env_to_list(char **env);
char					**ft_envsplit(char *env, char c);

// builtins

void					export_in_env(t_env **env, char *key, char *value);
int						ft_cd(char **arg, t_env *env);
int						ft_echo(char **arg);
int						ft_export(char **args, t_env **env);
void	export_plus_equal(t_env **env, char *arg, int i);
void					normal_export(t_env **env, char *arg);
int						ft_unset(char **arg, t_env **env);
int						ft_env(char **arg, t_env **env);
int						ft_exit(char **arg, int exit_status);
int						ft_pwd(t_env **env);
char					*ft_strjoin_3(char *s1, char *s2);

// exec

void					execute_cmd(t_execution **cmd_list, t_env **list_env);
void					init_cmd(t_execution **cmd_list, int n_cmds);
void					change_in_out(t_execution *cmd);
void					restore_std(int in, int out);
char					*find_path(t_execution *cmd, t_env **env);
void					execute_one_builtin(t_execution *cmd, t_env **env);
void					execute_execve_cmd(t_execution *cmd, t_env **env);
int						execute_builtins(t_execution *cmd, t_env **env);
void					ft_wait_child(t_execution *cmd, int *exit_status);

// pipe fonction
void	execute_pipe_cmd(t_execution **list_cmd, t_env **env);
void	handle_in(void);
void					set_exit_status(t_env **env, int exit_status);
void					printf_path_error(t_execution *cmd);
int	ft_lnum_export(int c);
void	shelvl_path_underscore(t_env **env_list);

#endif
