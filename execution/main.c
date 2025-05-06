#include "minishell.h"

// just init my struct 


t_execution	*init_test_cmd()
{
	t_execution *cmd = malloc(sizeof(t_execution));

	if (!cmd)
		return (NULL);

	int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC , 0666);

	cmd->cmd = ft_split("ls -la", ' ');  
	cmd->is_builtin = 0;             
	cmd->in_file = 0;
	cmd->out_file = fd;
	cmd->path = NULL;
	cmd->env = NULL;
	cmd->next = NULL;
	return (cmd);
}


int main(int argc, char **argv, char **envp)
{
	
	t_env *env = env_to_list(envp);
	t_execution *cmd_list;

	cmd_list = init_test_cmd();  
	if (!cmd_list)
		return (1);

	execute_cmd(&cmd_list, &env);


	return (0);
}

