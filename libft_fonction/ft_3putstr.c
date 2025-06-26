/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:21:52 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/23 16:22:12 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_3putstr(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		ft_putstr_fd(s1, 1);
	if (s2)
		ft_putstr_fd(s2, 1);
	if (s3)
		ft_putstr_fd(s3, 1);
	if (s4)
		ft_putstr_fd(s4, 1);
}

void	ft_3putstr_err(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putstr_fd(s3, 2);
	if (s4)
		ft_putstr_fd(s4, 2);
}
