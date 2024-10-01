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

int	mini_redirect(t_node *node, t_son *son, t_list_env *env)
{
	t_node	*current_node;
	int temp_stdout;
    int temp_stdin;

	temp_stdout = dup(STDOUT_FILENO);
    temp_stdin = dup(STDIN_FILENO);
	if (node->operation->type == REDIR_R)
	{
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
	}
	else if (node->operation->type == REDIR_L)
	{
		printf("\n\nHOLAAAA\n\n");
		current_node = node->left;
		son->fd_in = open(node->right->operation->read, O_RDONLY);
		if (son->fd_in < 0)
		{
			perror("input");
			exit (1);
		}
		dup2(son->fd_in, STDIN_FILENO);
		close(son->fd_in);
	}
	execute(son, env, current_node);
	dup2(temp_stdout, STDOUT_FILENO);
    dup2(temp_stdin, STDIN_FILENO);
    close(temp_stdout);
    close(temp_stdin);
	return (0);
}
