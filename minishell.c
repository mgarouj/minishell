/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:11 by fbelkass          #+#    #+#             */
/*   Updated: 2025/03/14 21:28:41 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char *line;

    line = readline("minishell>>");
    
    while (line)
    {
        if(!parssing(line))
        {
            print_err("syntax error missing quote");
        }
        else
            write(1,"great\n",6);
        line = readline("minishell>>");
    }
    return(0);
}
