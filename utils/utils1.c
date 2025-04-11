/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:03 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/07 16:03:14 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void print_err(char *str)
{
    int i;

    i = 0;
    write(2,"error :",7);
    while(str[i])
    {
        write(2,&str[i],1);
        i++;
    }
    write(2,"\n",1);
}


char *ft_strndup(char *s, size_t n)
{
    size_t i;
    char *dup;

    dup = (char *)malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *sub_str(char *s, int size)
{
    int i;
    char *r;
    
    r = (char *)malloc(size + 1);
    if (!r)
        return (NULL);

    i = 0;
    while (i < size)
    {
        r[i] = s[i];
        i++;
    }
    r[i] = '\0';
    
    return (r);
}

char	*ft_strdup(const char *s)
{
	size_t	l;
	size_t	i;
	char	*r;

	i = 0;
	l = ft_strlen(s);
	r = (char *)malloc((l + 1) * sizeof(char));
	if (!r)
	{
		return (NULL);
	}
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		slen = ft_strlen(s) - start;
	else
		slen = len;
	r = (char *)malloc((slen + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

int ft_strlen(char const *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;

    return(i);

}


char *ft_strtrim(char *s, int size)
{
    int start;
    int end;
    char *r;
    
    if (!s)
        return (NULL);
    
    start = 0;
    while (s[start] && (s[start] == ' ' || s[start] == '\t'))
        start++;
    end = size - 1;
    while (end > start && (s[end] == ' ' || s[end] == '\t'))
        end--;
    r = sub_str(s + start, end - start + 1);
    if(!r)
        return(NULL);
    return (r);
}


void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static size_t	count(char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

static char	**copy(char *s, char c, char **r)
{
	size_t	i;
	size_t	start;
	size_t	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			r[l] = ft_substr(s, start, i - start);
			l++;
		}
	}
	r[l] = NULL;
	return (r);
}

char	**ft_split(char *s, char c)
{
	char	**r;

	if (!s)
		return (NULL);
	r = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!r)
		return (NULL);
	return (copy(s, c, r));
}


int ft_strcmp(char *s1,char *s2)
{
    int i;

    i = 0;
    while(s1[i] || s2[i])
    {
        if(s1[i] != s2[i])
            return(0);
        i++;
    }
    return(1);
}