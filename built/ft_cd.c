#include "../minishell.h"

// This function checks if the path is valid
// If the path is NULL, it returns the HOME directory
// If the path is not NULL, it returns the path
// If the HOME environment variable is not set, it prints an error message
// and returns NULL
// If the path is valid, it returns the path

char *get_path(char **arg, t_env *env)
{
    char *path;

    if (!arg[1])
    {
        path = get_env_value("HOME", env);
        printf("%s\n", path);
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

    printf("cwd = %s \n", cwd);
    if (!cwd)
    {
        perror("getcwd");
        return (0);
    }
    change_env_value(&env, "OLDPWD", cwd);
    free(cwd);
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return (1);
    }
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

    // printf("cd ---------------------\n");
    path = get_path(arg, env);
    if (path)
        return (change_directory(path, env));
    return (1);
}
