/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:33:11 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 09:49:19 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_list_env *env_list)
{
	char	*path_value;
	char	**paths;

	path_value = NULL;
	paths = NULL;
	while (env_list)
	{
		if (ft_strncmp(env_list->content, "PATH=", 5) == 0)
		{
			path_value = env_list->content + 5;
			break ;
		}
		env_list = env_list->next;
	}
	if (path_value)
		paths = ft_split(path_value, ':');
	return (paths);
}
