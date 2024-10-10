/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:17:00 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/21 15:17:00 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_apendd(t_node *node, t_son *son)
{
	son->fd_out = open(node->right->operation->read,  O_APPEND | O_CREAT
			| O_RDWR, 0644);
	if (son->fd_out < 0)
	{
		perror("output");
		exit (1);
	}
	return (0);
}

t_node	*redir_r(t_son *son, t_node *node)
{
	t_node	*current_node;

	current_node = node->left;
	son->fd_out = open(node->right->operation->read, O_TRUNC | O_CREAT
			| O_RDWR, 0644);
	if (son->fd_out < 0)
	{
		perror("output");
		exit (1);
	}
	dup2(son->fd_out, STDOUT_FILENO);
	close(son->fd_out);
	return (current_node);
}

t_node	*redir_l(t_son *son, t_node *node)
{
	t_node	*current_node;

	current_node = node->left;
	if (node->left == NULL)
	{
		printf("Error: missing a command before the input redirection.\n");
		return (NULL);
	}
	if (node->right == NULL || node->right->operation == NULL
		|| node->right->operation->read == NULL)
	{
		printf("Error: file not specified in the input redirection.\n");
		return (NULL);
	}
	son->fd_in = open(node->right->operation->read, O_RDONLY);
	if (son->fd_in < 0)
	{
		perror("input");
		exit (1);
	}
	dup2(son->fd_in, STDIN_FILENO);
	close(son->fd_in);
	return (current_node);
}

int	mini_redirect(t_node *node, t_son *son, t_list_shellenv *shellenv)
{
	t_node	*current_node;
	int		temp_stdout;
	int		temp_stdin;

	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	if (node->operation->type == APPEND)
	{
		mini_apendd(node, son);
		current_node = node->left;
		dup2(son->fd_out, STDOUT_FILENO);
		close(son->fd_out);
	}
	if (node->operation->type == REDIR_R)
		current_node = redir_r(son, node);
	else
		current_node = redir_l(son, node);
	if (current_node == NULL)
		return (1);
	execute(son, shellenv, current_node);
	dup2(temp_stdout, STDOUT_FILENO);
	dup2(temp_stdin, STDIN_FILENO);
	close(temp_stdout);
	close(temp_stdin);
	return (0);
}
