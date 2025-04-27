/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_shi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkass <fbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:00 by fbelkass          #+#    #+#             */
/*   Updated: 2025/04/24 11:52:58 by fbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"



void handel_redin(char *filename, t_execution *exec)
{
    int fd;

    fd = open(filename, O_RDONLY);
    fd_collec(fd,1);
    if(fd == -1)
    {
        print_err("failed to open fd");
        fd_collec(0,0);
        return;
    }
    if(exec -> in_file != 0)
        close(exec -> in_file);
    exec -> in_file = fd;
}

void handel_reout(char *filename,t_execution *exec)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    fd_collec(fd,1);
    if(fd == -1)
    {
        print_err("failed to open fd");
        fd_collec(0,0);
        return;
    }
    if(exec->out_file != 1)
        close(exec->out_file);
    exec->out_file = fd;
}

void handel_redappend(char *filename, t_execution *exec)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    fd_collec(fd,1);
    if (fd == -1)
    {
        print_err("failed to open for append redirection");
        fd_collec(0,0);
        return;
    }
    if (exec->out_file != 1)
        close(exec->out_file);
    exec->out_file = fd;
}


void handel_heredoc(t_execution *exec,char *delimiter)
{
    int fd[2];
    char *line;

    if(!delimiter)
        return;
    if(pipe(fd) == -1)
    {
        print_err("heredoc error");
        return;
    }
    while(1)
    {
        line =readline("> ");
        if(!line)
        {
            print_err("herdoc");
            break;
        }
        if(!ft_strcmp(line,delimiter))
        {
            free(line);
            break;
        }
        write(fd[1],line,ft_strlen(line));
        write(fd[1],"\n",1);
        free(line);
    }
    close(fd[1]);
    if(exec->in_file != 0)
        close(exec->in_file);
    exec->in_file = fd[0];
}

//implimenting this 
char *get_and_remove_delimiter(char **str)
{
    char *delimiter;
    int i = 0;

    if (!str || !*str)
        return (NULL);
    while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t')
        i++;
    delimiter = sub_str(*str, i);
    if ((*str)[i])
    {
        while ((*str)[i] == ' ' || (*str)[i] == '\t')
            i++;
        if ((*str)[i])
        {
            char *new_value = ft_strdup(*str + i);
            free(*str);
            *str = new_value;
        }
        else
        {
            free(*str);
            *str = NULL;
        }
    }
    else
    {
        free(*str);
        *str = NULL;
    }

    return delimiter;
}


void heredoc(t_tokenn *token, t_execution *exec)
{
    t_tokenn *tmp;
    t_tokenn *to_delete;
    char *del;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == HEREDOC && tmp->next && tmp->next->type == EXP)
        {
            del = get_and_remove_delimiter(&tmp->next->value);
            handel_heredoc(exec, del);

            // If after handling, the value is NULL, we delete the node
            if (tmp->next->value == NULL)
            {
                to_delete = tmp->next;
                tmp->next = tmp->next->next;
                free(to_delete);
            }
        }
        tmp = tmp->next;
    }
}


int handel_red(t_tokenn *token,t_execution *exec)
{
    t_tokenn *tmp;
    
    tmp = token;
    while (tmp)
    {
        if(tmp->type == REDIRECTION_IN ||
            tmp->type == REDIRECTION_OUT ||
            tmp->type == REDIRECTION_AP || tmp->type == HEREDOC)
        {
            if (!tmp->next || tmp->next->type != EXP)
            {
                print_err("Syntax error: missing file after redirection");
                return(0);
            }
            if(tmp->type == REDIRECTION_IN)
                handel_redin(tmp->next->value,exec);
            else if(tmp->type == REDIRECTION_OUT)
                handel_reout(tmp->next->value,exec);
            else if(tmp->type == REDIRECTION_AP)
                handel_redappend(tmp->next->value,exec);
            else if(tmp->type == HEREDOC)
                heredoc(token,exec);
            if (tmp->next)
                tmp = tmp->next;
            else
                break;
        }
        else
                tmp = tmp->next;
    }
    return(1);
}
