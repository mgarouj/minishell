#include "../minishell.h"


char *get_path(char **arg, t_env *env)
{
    char *path;

    if (!arg[1])
    {
        path = get_env_value("HOME", env);
        if (!path)
        {
            ft_putstr_fd("cd: HOME not set\n", 1);
            return (NULL);
        }
        return (path);
    }
    return (arg[1]);
}

// This function changes the current working directory

int change_directory(char *path, t_env *env)
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("getcwd"), 0);
    change_env_value(&env, "OLDPWD", cwd);
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

// This function is called when the user types "cd" in the shell
// It changes the current working directory to the specified path
// If no path is specified, it changes to the HOME directory
// If the path is invalid, it prints an error message
// and returns 1
// If the path is valid, it updates the OLDPWD and PWD environment variables
// and returns 0

int ft_cd(char **arg, t_env *env)
{
    char *path;

    path = get_path(arg, env);
    if (path)
        return(change_directory(path, env));
    return (1);
}