
# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write
# include <stddef.h>     // NULL
# include <stdbool.h>
# include <stdio.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

enum token
{
	EXP,
	PIPE,
	REDIRECTION_IN, // <
	REDIRECTION_OUT, // >
	REDIRECTION_AP, // >>
	HEREDOC, // <<
};

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;


typedef struct s_tokenn
{
	enum token	type;
	char			*value;
	struct s_tokenn	*next;
}	t_tokenn;

typedef struct s_execution
{
	pid_t				pid;
	bool				is_builtin;
	char				*full_path;
	int pipe_fd[2];	
	bool				is_last;

	char				**cmd;
	int					in_file;
	int					out_file;
	char				**env;
	char				*path;
	struct s_execution	*next;
}	t_execution;


// typedef struct s_command
// {
// 	char				*name;
// 	char				**args;
// 	char				*path;
// 	t_red				*in;
// 	t_red				*out;
// 	int					fd;
// 	struct s_command	*next;
// }						t_command;



//libft fonction
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
int	ft_atoi(const char *str);
int	ft_lstsize(t_env *lst);
char	*ft_strdup(char *s1);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int	ft_isalnum(int c);
int	ft_lstsize_cmd_list(t_execution *cmd_list);
pid_t ft_fork(const char *msg);
int	ft_isalpha(int c);
void	ft_putstr_fd(char *s, int fd);

//env

void export_in_env(t_env **env, char *key, char *value);
void exit_value(t_env **env, int n);
t_env *find_var(t_env *env, char *key);

char	**ft_split(char const *s, char c);
char 	**ft_envsplit(char *env, char c);
char *get_env(t_env *env, char *target);

void change_env_value(t_env **env, char *key, char *new_value);
t_env *env_to_list(char **env);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_lstadd_back(t_env **lst, t_env *new);

// builtins
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
void init_cmd(t_execution **cmd_list);
void change_in_out(t_execution *cmd);
void restore_std(int in, int out);
char	*find_path(t_execution *cmd, t_env **env);
void execute_one_builtin(t_execution *cmd, t_env **env);
void execute_execve_cmd(t_execution *cmd, t_env **env);