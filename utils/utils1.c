/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:03 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/15 20:06:18 by fbelkass         ###   ########.fr       */
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
#include <stdlib.h>

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
