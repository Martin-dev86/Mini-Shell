/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:02:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/28 18:32:51 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_env(char **env)
{
	if (env== NULL)
		exit (128);
	else if (!getenv("PATH"))
		exit(1);
	else if (!getenv("USER"))
		exit(1);
	else if (!getenv("HOME"))
		exit(1);
	else if (!getenv("PWD"))
		exit(1);
	else if (!getenv("OLDPWD"))
	{
		perror("OLDPWD");
		exit(1);
	}
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
			exit(1);
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
