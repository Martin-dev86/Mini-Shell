/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:00:29 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 17:35:23 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * 1024);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, 1024) != NULL)
		return (cwd);
	else
	{
		perror("getcwd");
		free(cwd);
		return (NULL);
	}
}

int	mini_pwd(t_son *son, t_token *token)
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
		result = get_pwd();
		if (!result)
		{
			perror ("getpwd");
			exit (1);
		}
		mini_redirect(token, son);
		printf("%s\n", result);
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
