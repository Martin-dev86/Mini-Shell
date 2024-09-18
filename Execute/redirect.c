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
	(void)env;
	if (ft_strcmp(node->operation->read, ">") == 0)
	{
		son->fd_out = open(node->left->operation->read, O_TRUNC | O_CREAT
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
		son->fd_in = open(node->left->operation->read, O_RDONLY);
		if (son->fd_in < 0)
		{
			perror("input");
			exit (1);
		}
		dup2(son->fd_in, STDIN_FILENO);
		close(son->fd_in);
	}
	return (0);
}
