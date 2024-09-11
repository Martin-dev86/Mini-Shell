/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:27:44 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/03 22:27:44 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_pipes(t_son *son, int num_pipes)
{
    int i;

    son->fd = malloc(num_pipes * sizeof(int *));
    if (!son->fd)
        return (-1);
    i = 0;
    while (i < num_pipes)
    {
        son->fd[i] = malloc(2 * sizeof(int));
        if (!son->fd[i])
        {
            perror("malloc");
            return (-1);
        }
        if (pipe(son->fd[i]) == -1) 
        {
            perror("pipe");
            return (-1);
        }
        i++;
    }
    return (0);
}
int mini_pipe(t_token *token, t_list_env *env, t_son *son, int num_commands)
{
    int i = 0;

    if (create_pipes(son, num_commands - 1) == -1)
    {
        perror("Error creando pipes");
        exit(EXIT_FAILURE);
    }
    while (i < num_commands)
    {
        son->pid = fork();
        if (son->pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (son->pid == 0)
        {
            if (i > 0)
            {
                if (dup2(son->fd[i - 1][0], STDIN_FILENO) == -1)
                {
                    perror("dup2 stdin");
                    exit(EXIT_FAILURE);
                }
            }
            if (i < num_commands - 1)
            {
                if (dup2(son->fd[i][1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 stdout");
                    exit(EXIT_FAILURE);
                }
            }
            int j = 0;
            while (j < num_commands - 1)
            {
                close(son->fd[j][0]);
                close(son->fd[j][1]);
                j++;
            }

            if (execve(/* ruta del comando */, /* argumentos del comando */, env) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }

        i++;
    }
    i = 0;
    while (i < num_commands - 1)
    {
        close(son->fd[i][0]);
        close(son->fd[i][1]);
        i++;
    }

    i = 0;
    while (i < num_commands)
    {
      if (waitpid(son->pid, &son->code, 0) < 0)
	    {
		perror("waitpid");
		return (son->code);
	    }
    }
    return (son->code);
}