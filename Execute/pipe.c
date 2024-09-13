/* ************************************************************************** */
/*																		    */
/*														:::      ::::::::   */
/*   pipe.c										     :+:      :+:    :+:   */
/*												    +:+ +:+		 +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/03 22:27:44 by cagarci2		  #+#    #+#		     */
/*   Updated: 2024/09/03 22:27:44 by cagarci2		 ###   ########.fr       */
/*																		    */
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
int mini_pipe(t_token *token, t_list_env *env, t_son *son, t_node *node)
{
    int i = 0;

	if (create_pipes(son, node->n_childs - 1) == -1)
	{
		perror("Error creando pipes");
		exit(EXIT_FAILURE);
	}
	while (i < node->n_childs)
	{
		son->pid = fork();
		if (son->pid == -1)
			ft_exit("fork error", son->code);
		if (son->pid == 0)
		{
			if (i > 0)
			{
				if (dup2(son->fd[i - 1][0], STDIN_FILENO) == -1)
					ft_exit("dup2 error", son->code);
			}
			if (i < node->n_childs - 1)
			{
				if (dup2(son->fd[i][1], STDOUT_FILENO) == -1)
					ft_exit("dup2 error", son->code);
			}
			int j = 0;
			while (j < node->n_childs - 1)
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
    while (i < node->n_childs - 1)
    {
		close(son->fd[i][0]);
		close(son->fd[i][1]);
		i++;
    }

    i = 0;
    while (i < node->n_childs)
    {
      if (waitpid(son->pid, &son->code, 0) < 0)
	    {
		perror("waitpid");
		return (son->code);
	    }
    }
    return (son->code);
}