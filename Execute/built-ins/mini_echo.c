/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:20:09 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/21 13:12:14 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_echo(t_son *son, t_token *token)
{
	char	*result;

	son->pid = fork();
	if (son->pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (son->pid == 0)
	{
		result = token->content;
		if (!result)
		{
			perror ("echo");
			exit (1);
		}
		printf("%s", result);
		free (result);
		exit (0);
	}
	if (waitpid(son->pid, &son->code, 0) < 0)
	{
		perror("waitpid");
		return (son->code);
	}
	return (son->code);
}
