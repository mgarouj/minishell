/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:26:35 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/03 15:51:26 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_in_readline)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		exit_status(1, 130);
	}
	exit_status(1, 130);
}

void	sig_heredoc_child(int sig)
{
	(void)sig;
	fd_collec(0, 0);
	write(2, "\n", 1);
	exit(130);
}

void	signal_handler(int f)
{
	if (f == 1)
	{
		signal(SIGINT, sig_int_handler);
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
