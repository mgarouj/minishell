
# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write
# include <stddef.h>     // NULL
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

enum token
{
	EXP,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_AP,
	HEREDOC,
};

typedef struct s_envrmt
{
	char *key;
	char *value;
	int dx;
	struct s_envrmt *next;
}	t_envrmt;


typedef struct s_tokenn
{
	enum token	type;
	char			*value;
	struct s_tokenn	*next;
}	t_tokenn;

typedef struct s_execution
{
	char				**cmd;
	int					in_file;
	int					out_file;
    char                *path;
	char				**env;
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
int	ft_atoi(const char *str);
int	ft_lstsize(t_envrmt *lst);
char	*ft_strdup(char *s1);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int	ft_isalpha(int c);
int	ft_isalnum(int c);

//env

void export_in_env(t_envrmt **env, char *key, char *value);
void exit_value(t_envrmt **env, int n);
t_envrmt *find_var(t_envrmt *env, char *key);

char	**ft_split(char const *s, char c);
char 	**ft_envsplit(char *env, char c);
char *get_env(t_envrmt *env, char *target);

void change_env_value(t_envrmt **env, char *key, char *new_value);
t_envrmt *env_to_list(char **env);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_lstadd_back(t_envrmt **lst, t_envrmt *new);

// builtins
int ft_cd(char **arg, t_envrmt *env);
int ft_echo(char **arg);
int ft_export(char **args, t_envrmt **env);
void export_plus_equal(t_envrmt **env, char *arg);
void normal_export(t_envrmt **env, char *arg);
int ft_unset(char **arg, t_envrmt **env);
int ft_env(char **arg, t_envrmt **env);
int ft_exit(char **arg, int exit_status);