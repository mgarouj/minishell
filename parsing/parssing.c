/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:14:58 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/14 23:36:01 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"




// int find_quote(char *line)
// {
//     int i;

//     i = 0;
//     while(line[i])
//     {
//         if(line[i] == '"')
//             return(++i);
//         i++;
//     }
//     return(0);
// }

// int find_next_quote(char *line)
// {
//     int next;

//     next = find_quote(line);
//     if(next)
//     {
//         return(next);
//     }
//     else
//         return(0);

// }

// int parssing(char *line)
// {
//     int i;
//     int next;

//     i = 0;
//     next = find_quote(line);
//     if(next)
//     {
//         if(find_next_quote(line + next))
//         {
            
//         }
//     }


// }


int find_dquote(char *line, int *i)
{
    (*i)++;
    while(line[*i])
    {
        if(line[*i] == '"')
            return(1);
        (*i)++;
    }
    return(0);
}

int find_squote(char *line,int *i)
{
    (*i)++;
    while(line[*i])
    {
        if(line[*i] == '\'')
            return(1);
        (*i)++;
    }
    return(0);
}

int count(char *line,int *i,char t)
{
    int c;

    c = 0;
    while (line[*i] == t)
    {
        c++;
        (*i)++;
    }
    (*i)--;
        return(c <= 2);
}

int parssing(char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        if(line[i] == '"')
        {
            if (!find_dquote(line, &i))
                return(0);
        }
        else if(line[i] == '\'')
        {
            if(!find_squote(line , &i))
                return(0);
        }
        else if(line[i] == '<' || line[i] == '>')
        {
               if(!count(line,&i,line[i]))
                return(0);
        }
        i++;
    }
    return(1);
}