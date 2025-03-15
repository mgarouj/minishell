/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/15 20:06:09 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char *line;

    
    
    while (1)
    {
        line = readline("minishell ");
        // trim tabs spces 
        // if empty
        // continue
        if(!line)
        {
            continue;
        }
        
        line = ft_strtrim(line,ft_strlen(line));
        if(!line)
        {
            continue;
        }
        if (parssing(line) == 0)
            continue;
    }
    return(0);
}
