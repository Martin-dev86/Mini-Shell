/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:02:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 12:33:16 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_env(char **env)
{
	// Only keep the first if
	if (env == NULL || *env == NULL)
		ft_exit ("NO ENV",128);
	else if (!getenv("PATH"))
		ft_exit("NO PATH", EXIT_FAILURE);
	else if (!getenv("USER"))
		ft_exit("NO USER", EXIT_FAILURE);
	else if (!getenv("HOME"))
		ft_exit("NO HOME", EXIT_FAILURE);
	else if (!getenv("PWD"))
		ft_exit("NO PWD",EXIT_FAILURE);
	else if (!getenv("OLDPWD"))
		ft_exit("NO OLDPWD",EXIT_FAILURE);
}

t_list_env	*env_parse(char **env)
{
	t_list_env	*head;
	t_list_env	*new;
	t_list_env	*current;
	int			i;

	first_env(env);
	head = NULL;
	new = NULL;
	i = 0;
	while (env[i])
	{
		new = (t_list_env *)malloc(sizeof(t_list_env));
		if (!new)
			ft_exit("malloc failed", EXIT_FAILURE);
		new->content = ft_strdup(env[i]);
		new->next = NULL;
		if (head == NULL)
		{
			head = new;
			current = head;
		}
		else
		{
			current->next = new;
			current = new;
		}
		i++;
	}
	return (head);
}
