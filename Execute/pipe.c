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

void	close_wait(t_son *son, int n_child)
{
	int	i;

	i = 0;
	while (i < n_child - 1)
	{
		close(son->fd[i][0]);
		close(son->fd[i][1]);
		i++;
	}
	i = 0;
	while (i < n_child)
	{
		waitpid(son->pid, &son->code, 0);
		if (WIFEXITED(son->code))
			son->code = WEXITSTATUS(son->code);
		else if (WIFSIGNALED(son->code))
			son->code = 128 + WTERMSIG(son->code);
		i++;
	}
}

int	create_pipes(t_son *son, int num_pipes)
{
	int	i;

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

void	handle_child_process(t_son *son, t_node *current_node, \
	t_list_shellenv *shellenv)
{
	int	j;
	int	i;

	i = son->i;
	j = 0;
	if (i > 0)
		if (dup2(son->fd[i - 1][0], STDIN_FILENO) == -1)
			ft_exit("dup2 error", son->code);
	if (i < son->n_child - 1)
		if (dup2(son->fd[i][1], STDOUT_FILENO) == -1)
			ft_exit("dup2 error", son->code);
	while (j < son->n_child - 1)
	{
		close(son->fd[j][0]);
		close(son->fd[j][1]);
		j++;
	}
	if (current_node->operation->type != CMD)
		execute(son, shellenv, current_node);
	else
		mini_cmd(shellenv, son, current_node);
	exit(son->code);
}

void	forking(t_son *son, t_list_shellenv *shellenv, t_node *node)
{
	t_node	*current_node;

	if (son->flag == -1)
	{
		current_node = node->left;
		son->flag = 0;
	}
	else
		current_node = node->right;
	son->pid = fork();
	g_prompt_active = son->pid;
	if (son->pid == -1)
		ft_exit("fork error", son->code);
	if (son->pid == 0)
		handle_child_process(son, current_node, shellenv);
	son->pids[son->i] = son->pid;
}

int	mini_pipe(t_son *son, t_node *node, t_list_shellenv *shellenv)
{
	son->flag = -1;
	son->i = 0;
	son->pids = malloc(node->n_childs * sizeof(int));
	if (!son->pids)
		ft_exit("Memory allocation error", 1);
	if (create_pipes(son, node->n_childs - 1) == -1)
		ft_exit("Error create pipe", 128);
	son->n_child = node->n_childs;
	while (son->i < son->n_child)
	{
		forking(son, shellenv, node);
		if (node->right->operation->type == PIPE)
		{
			node = node->right;
			son->flag = -1;
		}
		son->i++;
	}
	close_wait(son, son->n_child);
	return (son->code);
}
