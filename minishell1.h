/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:44 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/13 20:46:11 by fbelkass         ###   ########.fr       */
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

// Token types
enum e_token
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

// Token struct
typedef struct s_tokenn
{
	enum e_token	type;
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

// Parsing
int			parssing(char *line); // Typo: consider renaming to parsing
char		*ft_strtrim(char *s, int size);
char		*ft_strndup(char *s, int n);
t_tokenn	*tokenize(char *line);
void		handel_env(char *s, t_env **env); // Typo: consider renaming to handle_env
void		expanding(t_tokenn *t, t_env *l);
void print_err(char *str);
int ft_strlen(char *str);


char	*ft_substr(char *s, unsigned int start, int len);
void	free_split(char **split);
int		count(char *s, char c);


// Utils
char	*ft_strdup(char *s);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*sub_str(char *s, int size);
int			ft_strlcat(char *dst, char *src, int dstsize);
int			ft_strlcpy(char *dst, char *src, int dstsize);

#endif // MINISHELL_H