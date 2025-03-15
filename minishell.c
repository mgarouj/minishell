/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/15 20:57:03 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char *line;
    char *trim;
    
    while (1)
    {
        line = readline("minishell ");
        // trim tabs spces 
        // if empty
        // continue
        
        if (!line)
        {
            print_err("exit");
            break;
        }
        
        trim = ft_strtrim(line,ft_strlen(line));
        free(line);
        line = trim;
        
        if(!line || line[0] == '\0')
        {
            free(line);
            continue;
        }
        if (parssing(line) == 0)
        {
            free(line);
            continue;
        }
        free(line);
         
    }
    return(0);
}
