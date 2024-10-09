/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:20:09 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/09 20:33:02 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_loop(t_node *node)
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
		printf("%s ", result);
		free (result);
		node = node->right;
	}
}

int	mini_echo(t_node *node)
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
	echo_loop(node);
	if (flag == 0)
		printf("\n");
	return (0);
}
