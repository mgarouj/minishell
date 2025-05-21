/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:14:12 by mgarouj           #+#    #+#             */
/*   Updated: 2025/05/21 14:12:00 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// This function changes the current working directory

int change_directory(char *path, t_env *env)
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("getcwd"), 0); // this line 
    change_env_value(&env, "OLDPWD", cwd);
    //if input .. take path /home/mgarouj/Desktop/my_project/c4/execution/a/a  /home/mgarouj/Desktop/my_project/c4/execution/a/
    free(cwd);
    if (chdir(path) == -1)
        return (perror("cd"), 1);
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("getcwd"), 1);
    change_env_value(&env, "PWD", cwd);
    free(cwd);
    return (0);
}

int ft_cd(char **arg, t_env *env)
{
    char *path;

    if (!arg[1])
    {
        path = get_env_value("HOME", env);
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 1);
            return (1);
        }
    }
    else
        path = arg[1];
    if (path)
        return(change_directory(path, env));
    return (1);
}
