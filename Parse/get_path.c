/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:33:11 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 00:09:07 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_list_env *env_list)
{
    char *path_value = NULL;
    char **paths = NULL;

    while (env_list)
    {
        if (ft_strncmp(env_list->content, "PATH=", 5) == 0)
        {
            path_value = env_list->content + 5;
            break;
        }
        env_list = env_list->next;
    }
    if (path_value)
        paths = ft_split(path_value, ':');

    return paths;
}