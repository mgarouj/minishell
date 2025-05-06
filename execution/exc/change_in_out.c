#include "../minishell.h"

void change_in_out(t_execution *cmd)
{
    if (cmd->in_file != 0)
	{
		dup2(cmd->in_file, 0);
		close(cmd->in_file);
	}
	if (cmd->out_file != 1)
	{
		dup2(cmd->out_file, 1);
		close(cmd->out_file);
	}
}

void restore_std(int in, int out)
{
    dup2(in, 0);  // restore stdin
    dup2(out, 1); // restore stdout
    close(in);
    close(out);
}