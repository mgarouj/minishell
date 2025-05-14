/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:03 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/13 21:16:56 by fbelkass         ###   ########.fr       */
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


char *ft_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i])
        i++;

    while (src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';
    return dest;
}

char *ft_strchr(char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
}


int	ft_strcmp(char *s1,char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_putstr_fd(char *s,int fd)
{
    if(!s)
        return;
    write(fd,s,ft_strlen(s));
}

// char *ft_strstr(char *haystack, char *needle)
// {
//     int i;
//     int j;

//     if (!*needle)
//         return (char *)haystack;

//     i = 0;
//     while (haystack[i])
//     {
//         j = 0;
//         while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j])
//             j++;
//         if (needle[j] == '\0')
//             return ((char *)(haystack + i));
//         i++;
//     }
//     return (NULL);
// }


int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;

    return(i);

}

char *ft_strndup(char *s, int n)
{
    int i;
    char *dup;

    dup = gar_coll(n + 1, 'a');
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
    
    r = gar_coll(size + 1, 'a');
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



char *ft_strdup(char *s)
{
    int l;
    int i;
    char *r;

    i = 0;
    l = ft_strlen(s);
    r = gar_coll((l + 1) * sizeof(char), 'a');
    if (!r)
        return (NULL);
    while (s[i])
    {
        r[i] = s[i];
        i++;
    }
    r[i] = '\0';
    return (r);
}

char *ft_substr(char *s, unsigned int start, int len)
{
    char *r;
    int i;
    int slen;

    if (!s)
        return (NULL);
    if (start > ft_strlen(s) || len == 0)
        return (ft_strdup(""));
    if (ft_strlen(s) - start < len)
        slen = ft_strlen(s) - start;
    else
        slen = len;
    r = (char *)gar_coll((slen + 1) * sizeof(char), 'a');
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


int	count(char *s, char c)
{
	int	i;
	int	j;

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
	int	i;
	int	start;
	int	l;

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

char **ft_split(char *s, char c)
{
    char **r;

    if (!s)
        return (NULL);
    r = (char **)gar_coll((count(s, c) + 1) * sizeof(char *), 'a');
    if (!r)
        return (NULL);
    return (copy(s, c, r));
}


