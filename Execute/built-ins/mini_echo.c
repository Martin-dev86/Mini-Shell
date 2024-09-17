/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:20:09 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/18 00:00:05 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_echo(t_node *node)
{
	char	*result;

	while(node->right)
	{
		result = node->operation->read;
		if (!result)
		{
			perror ("echo");
			exit (1);
		}
			printf("%s", result);
		free (result);
		node = node->right;
	}
	return (0);
}
