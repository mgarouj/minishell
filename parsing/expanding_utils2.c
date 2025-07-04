/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:59:13 by fbelkass          #+#    #+#             */
/*   Updated: 2025/07/04 16:23:44 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_expandable_dollar(char *exp, int i, t_expand_data *data)
{
	return (exp[i] == '$' && data->sh_expand && exp[i + 1] && (ft_isalnum(exp[i
					+ 1]) || exp[i + 1] == '_' || exp[i + 1] == '?' || exp[i
				+ 1] == '$'));
}
