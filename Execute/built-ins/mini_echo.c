/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:20:09 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/18 19:30:58 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(t_node *node)
{
	char	*result;
	int		flag;

	flag = 0;
	if (ft_strcmp(node->right->operation->read, "-n") == 0)
	{
		flag = 1;
		node = node->right;
	}
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
	if (flag == 0)
		printf("\n");
	return (0);
}
