#include "../minishell.h"

char *check_line(char *line, t_env *env_s)
{
    line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
    if (!line)
    {
        print_err("exit");
        set_exit_status(&env_s, env_s->exit_status);
        exit_minishell(env_s->exit_status);
    }
    return (line);
}

t_tokenn *tr_par(t_tokenn *token, char *line, t_env *env)
{
    char *trim;
    add_history(line);
    trim = ft_strtrim(line, ft_strlen(line));
    free(line);
    if (!trim || trim[0] == '\0')
        continue ;
    if (!parssing(trim))
    {
        l->exit_status = 2;
        continue ;
    }
    token = tokenize(trim);
    return (token);
}