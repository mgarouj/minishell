/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:44 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/29 14:55:12 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_in_readline ;

typedef enum e_token
{
	EXP,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_AP,
	HEREDOC,
}						t_token;

typedef enum e_context_type
{
	CTX_EXPORT_RHS,
	CTX_EXPORT_DIRECT,
	CTX_COMMAND_ARG
}						t_context_type;

typedef struct s_tokenn
{
	t_token				type;
	char				*value;
	int					quotes;
	int					expan_toex;
	struct s_tokenn		*next;
}						t_tokenn;

typedef struct s_export
{
	char				*key;
	char				*value;
	int					flag_env;
	struct s_export		*next;
}						t_export;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					exit_status;
	int					printed;
	char				*pwd;
	t_export			*export;
	struct s_env		*next;
}						t_env;

typedef struct s_herdoc
{
	pid_t				pid;
	int					fd_write;
	int					fd_read;
	int					exit_status;
	char				*line;
	char				*tmp;
}						t_her;

typedef struct s_expand_data
{
	t_env				*env;
	int					expanded;
	int					expanded_toexe;
	int					sh_expand;
	int					quoted;

}						t_expand_data;

typedef struct s_execution
{
	pid_t				pid;
	bool				is_builtin;
	int					pipe_fd[2];
	bool				is_last;
	int					flag_expand;
	char				**cmd;
	int					in_file;
	int					out_file;
	int					skip;
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

int						parssing(char *line);
void					handle_execve_error(t_execution *cmd, struct stat *st);
void					ft_3putstr_err(char *s1, char *s2, char *s3, char *s4);
t_tokenn				*tokenize(char *line);
void					handel_env(char *s, t_env **env);
int						expand_rm_quotes(t_tokenn *t, t_env *l);
int						split_cmd(t_tokenn *token, t_execution **exec,
							t_env *env);
void					signal_handler(int f);
void					retoken(t_tokenn *token);
void					skip_quotes(const char *line, int *i, char quote);
char					*trim_line(char *line);
void					exit_minishell(int exit_s);
int						handle_eof(char *line);
t_env					*init_env(char **env);

void					print_err_ex(char *str, char *s2);
void					fd_collec(int fd, int mode);
void					*gar_coll(int size, char flag);
int						main_steps(char *line, t_env *env, t_execution **exec);
int						check_env_key(char *key, t_env *env);
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
int						is_num(char c);
void					add_token(t_tokenn **head, t_tokenn *new_token);
int						is_operator(char c);
void					skip_whitespace(char *line, int *i);
char					*str_append(char *s1, char *s2);
char					*str_append_char(char *s, char c);
char					*get_env_value(char *key, t_env *env);
char					*expand_variable(char *exp, int *i, char *result,
							t_expand_data *data);
char					*handle_single_quote(char *exp, int *i, char *result);
int						handle_retoken(t_tokenn *tmp, t_expand_data *data);
int						retokenn(t_tokenn *token);
int						has_eq_before_space(char *s);
int						needs_retoken(char *value);
int						handle_expand_token(t_tokenn *tmp, t_tokenn *prev,
							t_expand_data *data, t_env *env);
char					*handel_afterd(char *exp, t_expand_data *data);
int						is_valid_identifier(const char *s);
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
void					init_env_cmd(t_env *env, t_execution **cmd);
t_execution				*creat_node(int expanded);
void					add_node_to_list(t_execution **exec, t_execution *node);
int						is_redirection(t_token s);
int						calculate_required_size(char *exp, t_execution *exec);
int						copy_and_append_cmd(char **new_cmd, t_execution *exec,
							char *exp);
int						check_c_heredoc(int c);
int						should_skip_token(t_tokenn *tmp, t_tokenn *prev);
int						append_to_cmd(char *exp, t_execution *exec);
int						check_writable_file(char *filename);
void					initialize(t_tokenn **here, t_tokenn *tmp, int *c);
int						handel_redirections(t_tokenn *token, t_tokenn *name,
							t_execution *exec);
int						handel_redin(char *filename, t_execution *exec);
int						handel_reout(char *filename, t_execution *exec);
int						handel_redappend(char *filename, t_execution *exec);
int						heredoc(char *delimiter, int quotes, t_execution *exec,
							t_env *env);
char					*handel_afterd_inherdoc(char *exp, t_env *env);
char					*get_env_value(char *key, t_env *env);
void					change_env_value(t_env **env, char *key,
							char *new_value);
t_env					*find_var(t_env *env, char *key);
void					ft_lstadd_back(t_env **lst, t_env *new);
void					export_in_env(t_env **env, char *key, char *value,
							int printed);
int						ft_cd(char **arg, t_env *env);
int						ft_echo(char **arg);
int						ft_export(char **args, t_env **env);
void					export_plus_equal(t_env **env, char *arg, int i);
void					normal_export(t_env **env, char *arg);
int						ft_unset(char **arg, t_env **env);
int						ft_env(char **arg, t_env **env);
int						ft_exit(char **arg, int exit_status);
int						ft_pwd(t_env **env);
char					*ft_strjoin_3(char *s1, char *s2);
void					null_value(t_env **env, char *arg);
char					**change_envlist_to_envchar(t_env *env);
void					execute_cmd(t_execution **cmd_list, t_env **list_env);
void					init_cmd(t_execution **cmd_list, int n_cmds);
void					change_in_out(t_execution *cmd);
void					restore_std(int in, int out);
char					*find_path(t_execution *cmd, t_env **env);
void					execute_one_builtin(t_execution *cmd, t_env **env);
void					execute_execve_cmd(t_execution *cmd, t_env **env);
int						execute_builtins(t_execution *cmd, t_env **env);
void					ft_wait_child(t_execution *cmd, int *exit_status);
void					handle_pipe_exit(t_execution **list_cmd, t_env **env,
							int *status);
void					handle_execve_exit(int status, t_env **env);

void					print_main(t_env *env_list, char *line);
void					execute_pipe_cmd(t_execution **list_cmd, t_env **env);
void					handle_in(void);
int						set_exit_status(int type, int new_status);
void					printf_path_error(t_execution *cmd, t_env *env);
int						ft_lnum_export(int c);
void					shelvl_path_underscore(t_env **env_list);
void					ft_wait_child(t_execution *cmd, int *exit_status);
void					handle_in(void);
void					handle_invalid_path(t_execution *cmd, t_env **env,
							char *path);
void					execve_command_handler(t_execution *cmd, t_env **env);
t_tokenn				*create_token(t_token type, char *value, int quotes);

#endif
