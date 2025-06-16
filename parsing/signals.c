/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:26:35 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/16 21:21:48 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}


void	sig_heredoc_child(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	exit(130);
}

void	signal_handler(int f, t_env *l)
{
	if (f == 1)
	{
		signal(SIGINT, sig_int_handler);
		set_exit_status(&l, 130);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (f == 2)
	{
		signal(SIGINT, sig_heredoc_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
