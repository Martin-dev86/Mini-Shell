/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:00:29 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/16 16:05:50 by cagarci2         ###   ########.fr       */
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

int	mini_pwd(t_son *son)
{
	char	*result;

	result = get_pwd();
	if (!result)
		ft_exit("pwd error", son->code);
	printf("%s\n", result);
	free (result);
	return (son->code);
}


