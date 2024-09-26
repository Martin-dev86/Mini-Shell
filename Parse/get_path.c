/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:33:11 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/26 12:30:00 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char *path)
{
	char	**paths;
	char	*tmp;

	paths = ft_calloc(0, sizeof(char *));
	tmp = ft_strtrim(path, ":");
	paths = ft_split(tmp, ':');
	free(tmp);
	return (paths);
}