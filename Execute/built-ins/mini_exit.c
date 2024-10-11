/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:53:57 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 09:25:37 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_node *node, t_list_shellenv *shellenv, \
	t_son *son, int status)
{
	int	exit_status;

	exit_status = status;
	if (!node || !node->operation || !node->operation->read)
	{
		printf("exit: invalid node or operation\n");
		exit(1);
	}
	if (node->right != NULL)
		exit_status = ft_atoi(node->right->operation->read);
	else
		exit_status = son->code;
	rl_clear_history();
	(void) node;
	(void) shellenv;
	(void) son;
	exit(exit_status);
}
