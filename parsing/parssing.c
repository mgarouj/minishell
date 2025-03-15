/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:14:58 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/15 16:59:37 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"



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

int count_redirection(char *line,int *i,char t)
{
    int c;

    c = 0;
    while (line[*i] == t)
    {
        c++;
        (*i)++;
    }
    (*i)--;
    // if(c == 3)
    //     print_err("")
        return(c <= 2);
}

int parss_pipe(char *line,int *i)
{
    if((*i) == 0)
        return(0);
    else if(line[*i] != ' ' && line[(*i) + 1] == '\0')
        return(0);
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
                {
                    print_err("syntax error missing quote");
                    return(0);
                }
        }
        else if(line[i] == '\'')
        {
            if(!find_squote(line , &i))
            {
                print_err("syntax error missing quote");
                return(0);
            }
        }
        else if((line[i] == '<' && line[i + 1] == '>') || (line[i] == '>' && line[i + 1] == '<'))
            return(0);
        else if(line[i] == '<' || line[i] == '>')
        {
               if(!count_redirection(line,&i,line[i]))
               {
                print_err("error");
               }
                return(0);
        }
        else if(line[i] == '|')
        {
            if(!parss_pipe(line,&i))
            {
                print_err("syntax error near unexpected token `|'");
                return(0);
            }
        }
        i++;
    }
    return(1);
}
