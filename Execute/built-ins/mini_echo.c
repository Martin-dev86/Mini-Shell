/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:20:09 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/10 23:29:12 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_loop(t_node *node, t_son *son)
{
	char	*result;

	while (node->right)
	{
		result = node->right->operation->read;
		if (!result)
		{
			perror ("echo");
			exit (1);
		}
		if (son->code != 0)
			break ;
		printf("%s ", result);
		free (result);
		node = node->right;
	}
}

int	mini_echo(t_node *node, t_son *son)
{
	int		flag;

	flag = 0;
	if (!node->right)
	{
		printf("\n");
		return (0);
	}
	if (ft_strcmp(node->right->operation->read, "-n") == 0)
	{
		flag = 1;
		node = node->right;
	}
	echo_loop(node, son);
	if (flag == 0)
		printf("\n");
	return (0);
}
