/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:44 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/04 19:17:36 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write
# include <stddef.h>     // NULL
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>

// Token types
enum token
{
	EXP,
	PIPE,
	REDIRECTION_IN, // <
	REDIRECTION_OUT, // >
	REDIRECTION_AP, // >>
	HEREDOC, // <<
};

// Token struct
typedef struct s_tokenn
{
	enum token	type;
	char			*value;
	struct s_tokenn	*next;
}	t_tokenn;

// Environment variable struct
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Execution struct
typedef struct s_execution
{
	char				**cmd;
	int					in_file;
	int					out_file;
	char				**env;
	struct s_execution	*next;
}	t_execution;

// Garbage collector struct
typedef struct s_gc
{
	void			*ptr;
	bool			is_free;
	struct s_gc		*next;
}	t_gc;

typedef struct s_fd_gc {
    int             fd;
    struct s_fd_gc *next;
} t_fd_gc;

// Parsing
int			parssing(char *line); // Typo: consider renaming to parsing
char		*ft_strtrim(char *s, int size);
char		*ft_strndup(char *s, int n);
t_tokenn	*tokenize(char *line);
void		handel_env(char *s, t_env **env); // Typo: consider renaming to handle_env
void remove_quotes(t_tokenn *t,t_env *l);
void print_err(char *str);
int ft_strlen(char *str);
int handel_red(t_tokenn *token,t_execution *exec);
int	heredoc(t_tokenn *token, t_execution *exec);
int split_cmd(t_tokenn *token,t_execution **exec);

char	*ft_substr(char *s, unsigned int start, int len);
void	free_split(char **split);
int		count(char *s, char c);

void fd_collec(int fd, int mode);
void	*gar_coll(size_t size, int flag, bool is_free);

// Utils
char *ft_strchr(char *s, int c);
char *ft_strcat(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
int	find_dquote(char *line, int *i);
char	*ft_strdup(char *s);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*sub_str(char *s, int size);
int			ft_strlcat(char *dst, char *src, int dstsize);
int			ft_strlcpy(char *dst, char *src, int dstsize);
char *ft_strstr(char *haystack, char *needle);
void ft_putstr_fd(char *s,int fd);
char	*ft_strldup(const char *s, int len);
#endif // MINISHELL_H