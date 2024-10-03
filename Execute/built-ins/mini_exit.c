/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:53:57 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/03 17:38:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_node *node, t_list_env *env, t_son *son, int status)
{
    int		exit_status;

	exit_status = status;
	if (!node || !node->operation || !node->operation->read)
	{
		fprintf(stderr, "exit: invalid node or operation\n");
		exit(1);
	}
	if (node->right != NULL)
		exit_status = ft_atoi(node->right->operation->read);
	else
		exit_status = son->code;
	rl_clear_history();
	(void) node;
	(void) env;
	(void) son;
	//t_free_node(node);
	//ft_free_env_list(env);
	//ft_free_son(son);

	exit(exit_status);
}
