/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:02:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 00:04:53 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		ft_exit("calloc failed", EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	calculate_length(const char *content)
{
	if (content != NULL)
		return (ft_strlen((content)));
	else
		return (0);
}

// Función para agregar un nuevo nodo a la lista
void	add_node_to_list(t_list_env **head, char *content)
{
	t_list_env	*new;
	t_list_env	*current;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env));
	if (!new)
		ft_exit("malloc failed", EXIT_FAILURE);
	new->content = ft_strdup(content);
	new->len = calculate_length(content);
	new->variable_len = new->len;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		current = *head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new;
	}
}

// Función para crear la lista enlazada desde las variables de entorno
t_list_env	*create_env_list(char **env)
{
	t_list_env	*head;
	int			i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		add_node_to_list(&head, env[i]);
		i++;
	}
	return (head);
}

t_list_env	*env_parse(char **env)
{
	t_list_env	*head;

	first_env(env);
	head = create_env_list(env);
	head->env = get_env(env);
	head->path = get_path(head);
	return (head);
}
