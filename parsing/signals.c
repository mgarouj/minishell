/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:26:35 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/27 09:52:16 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	sig_int_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	fd_collec(0, 0);
	rl_redisplay();
	g_env_exitval->exit_status = 130;
}

void	sig_heredoc_child(int sig)
{
	(void)sig;
	fd_collec(0, 0);
	write(2, "\n", 1);
	exit(130);
}

void	signal_handler(int f, t_env *l)
{
	(void)l;
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
