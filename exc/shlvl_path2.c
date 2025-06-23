/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_path2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:00:59 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/20 19:26:46 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_in(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("not running in interactive mode. Exiting...\n", 2);
		exit(1);
	}
}
