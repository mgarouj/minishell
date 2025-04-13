/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/13 20:47:07 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char *line;
    char *trim;
    int i;
    t_env *l;
    t_tokenn *token;
    
    l = NULL;
    i = 0;
    while(env[i])
    {
        handel_env(env[i],&l);
        i++;
    }
    
    while (1)
    {
        line = readline("prompt ");
        // trim tabs spces
        // if empty
        // continue
        
        if (!line)
        {
            print_err("exit");
            break;
        }
        if(line[0] != '\0')
            add_history(line);
        
        trim = ft_strtrim(line,ft_strlen(line));
        free(line);
        line = trim;
        
        if(!line || line[0] == '\0')
        {
            free(line);
            continue;
        }
        if (!parssing(line))
        {
            free(line);
            continue;
        }
        token = tokenize(line);
        expanding(token, l);
        while (token)
        {
            printf("Type: %d, Value: %s \n", token->type, token->value);
            token = token->next;
        }
        
        free(line);
         
    }
   
    return(0);
}
