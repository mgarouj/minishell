



#include "../minishell.h"



t_env *create_env(char *key, char *value)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}

void add_env(t_env **head, t_env *new_env)
{
    t_env *temp;

    if (!*head)
    {
        *head = new_env;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_env;
}



void handel_env(char *s,t_env **env)
{
    char **l;

    l = ft_split(s,'='),

    add_env(env,create_env(l[0],l[1]));

}

#include <stdio.h>

void print_env(t_env *l)
{
    t_env *tmp;
    tmp = l;

    while (tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = l -> next;
    }
    
}

int main()
{
    t_env *l = NULL;

    handel_env("HOME=fbelkasshshhs hfhhf",&l);

    print_env(l);
}