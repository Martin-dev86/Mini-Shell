/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:00:29 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/16 14:23:02 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
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
