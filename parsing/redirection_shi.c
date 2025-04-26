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


void handel_heredoc(t_execution *exec,t_tokenn *delimiter)
{
    int fd[2];
    char *line;
    char *del;

    if(!delimiter)
        return;
    del = ft_strtrim(delimiter->value,ft_strlen(delimiter->value));
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
        if(!ft_strcmp(line,del))
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

void heredoc(t_tokenn *token,t_execution *exec)
{
    t_tokenn *tmp;
    
    tmp = token;
    while(tmp)
    {
        if(tmp->type == HEREDOC && tmp->next)
            handel_heredoc(exec,tmp->next);
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
            tmp = tmp->next->next;
        }
        else
            tmp = tmp->next;
    }
    return(1);
}
