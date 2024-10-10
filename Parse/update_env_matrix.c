/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:32:09 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 12:39:43 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_matrix(char **env_matrix)
{
	size_t	i;

	i = 0;
	while (env_matrix[i])
	{
		free(env_matrix[i]);
		i++;
	}
	free(env_matrix);
}

size_t	count_env_list(t_list_env *env_list)
{
	size_t		count;
	t_list_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**create_env_matrix(t_list_env *env_list)
{
	size_t		count;
	char		**env_matrix;
	size_t		i;
	t_list_env	*current;

	if (!env_list)
		return (NULL);
	free_env_matrix(env_list->env);
	count = count_env_list(env_list);
	env_matrix = ft_calloc((count + 1), sizeof(char *));
	if (!env_matrix)
		return (NULL);
	current = env_list;
	i = 0;
	while (current && i < count)
	{
		env_matrix[i] = ft_strdup(current->content);
		if (!env_matrix[i])
			return (NULL);
		current = current->next;
		i++;
	}
	env_matrix[count] = NULL;
	return (env_matrix);
}
