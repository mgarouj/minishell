/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:11:53 by fbelkass          #+#    #+#             */
/*   Updated: 2025/06/22 21:41:57 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void    print_main(t_env *env_list, char *line)
{
    if (!line)
    {
        print_err("exit");
        set_exit_status(&env_list, env_list->exit_status);
        exit_minishell(env_list->exit_status);
    }
}

char *trim_line(char *line)
{
    char *trim;
    
    add_history(line);
    trim = ft_strtrim(line,ft_strlen(line));
    free(line);
    return(trim);
}


int main_steps(char *line,t_env *env,t_execution **exec)
{
    t_tokenn *token;
    
    token = NULL;

    if (!line || line[0] == '\0')
	        return(0) ;
	if (!parssing(line))
	{
			env->exit_status = 2;
			return(0);
	}
	token = tokenize(line);
	if (!expand_rm_quotes(token, env))
				return(0);
    if (!split_cmd(token, exec, env))
				return(0);
    return(1);
}

