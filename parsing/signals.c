/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:26:35 by fbelkass          #+#    #+#             */
/*   Updated: 2025/05/12 16:07:25 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void sig_int_handler(int sig)
{
    (void)sig;
    write(1,"\n",1);
    rl_on_new_line();
    // rl_replace_line("",1);
    rl_redisplay();
    
}

void signal_handler(void)
{   
    signal(SIGINT,sig_int_handler);
    signal(SIGQUIT, SIG_IGN);  
}
