/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:20:09 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/16 16:32:30 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_echo(t_token *token)
{
	char	*result;
	int		i;

	i = 0;
	while(++i < token->len)
	{
		result = token->argument[i];
		if (!result)
		{
			perror ("echo");
			exit (1);
		}
			printf("%s", result);
		free (result);
	}
	return (0);
}
