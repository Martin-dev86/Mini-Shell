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
	if (ft_strcmp(node->operation->read, ">") == 0)
	{
		current_node = node->left;
		printf("REDIR LEFT == %s\n\n", current_node->operation->read);
		fflush(stdout);
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
	else if (ft_strcmp(node->operation->read, "<") == 0)
	{
		current_node = node->left;
		printf("REDIR NODE == %s\n\n", node->left->operation->read);
		printf("REDIR RIGHT == %s\n\n", current_node->operation->read);
		fflush(stdout);
		son->fd_in = open(node->right->operation->read, O_RDONLY);
		if (son->fd_in < 0)
		{
			perror("input");
			exit (1);
		}
		dup2(son->fd_in, STDIN_FILENO);
		close(son->fd_in);
	}
	printf("REDIR RIGHT == %s\n\n", current_node->operation->read);
	printf("CURRENT NODE == %s\n\n", node->operation->read);
	fflush(stdout);
	execute(son, env, current_node);
	dup2(temp_stdout, STDOUT_FILENO);
    dup2(temp_stdin, STDIN_FILENO);
    close(temp_stdout);
    close(temp_stdin);
	return (0);
}
