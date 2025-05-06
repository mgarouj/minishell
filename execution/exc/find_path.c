#include "../minishell.h"

void	free_paths(char **paths)
{
	int i = 0;
	if (!paths)
		return;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char *check_path(char **path, t_execution *cmd)
{
    int i;
    char *test;
    char *full;

    i = 0;
    while (path[i])
    {
        test = ft_strjoin(path[i], "/");
		full = ft_strjoin(test, cmd->cmd[0]);
		free(test);
		if (access(full, X_OK) == 0)
		{
			free_paths(path);
			return (full);
		}
		free(full);
		i++;
	}
	free_paths(path);
	return (NULL);
}

char    *find_path(t_execution *cmd, t_env **env)
{
	char *env_path;
	char **path;
	if (!cmd || !cmd->cmd[0] || !cmd->cmd)
		return (NULL);
	if (ft_strchr(cmd->cmd[0], '/'))
		return (ft_strdup(cmd->cmd[0]));
	env_path = get_env(*env, "PATH");
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	return (check_path(path, cmd));
}
