/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:53:57 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/02 19:19:48 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_skips_all_but_numbers(char *str)
{
	while (*str && (*str < '0' || *str > '9'))
		str++;
	return (ft_atoi(str));
}

void	mini_exit(t_node *node, t_list_env *env, t_son *son, int status)
{
    int		exit_status;
	char	*str;

	str = node->operation->read;
	exit_status = status;
	if (!node || !node->operation || !node->operation->read)
	{
		fprintf(stderr, "exit: invalid node or operation\n");
		exit(1);
	}
	if (node->right != NULL)
		exit_status = ft_atoi(node->right->operation->read);
	else
		exit_status = ft_atoi_skips_all_but_numbers(str);

	rl_clear_history();
	t_free_node(node);
	ft_free_env_list(env);
	ft_free_son(son);

	exit(exit_status);
}
