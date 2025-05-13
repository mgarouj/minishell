




#include "minishell.h"


void print_env(t_env *l)
{
    t_env *tmp;
    tmp = l;

    while (tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp -> next;
    }
    
}

int main(int ac, char **av, char **env)
{
    t_env *l = NULL;

    l = env_to_list(env);

    print_env(l);
    return(0);

}