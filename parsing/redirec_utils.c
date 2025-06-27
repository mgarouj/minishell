/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:00:59 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/27 19:10:19 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_writable_file(char *filename)
{
	struct stat	st;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) != 0)
			return (print_err_ex(": Permission denied", filename), 0);
		if (stat(filename, &st) == 0 && S_ISDIR(st.st_mode))
			return (print_err_ex(": Is a directory", filename), 0);
	}
	return (1);
}
