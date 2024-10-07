/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:02:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/04 23:04:29 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_env(char **env)
{
	// Only keep the first if
	if (env == NULL || *env == NULL)
		ft_exit ("NO ENV", 128);
	else if (!getenv("PATH"))
		ft_exit("NO PATH", EXIT_FAILURE);
	else if (!getenv("USER"))
		ft_exit("NO USER", EXIT_FAILURE);
	else if (!getenv("HOME"))
		ft_exit("NO HOME", EXIT_FAILURE);
	else if (!getenv("PWD"))
		ft_exit("NO PWD", EXIT_FAILURE);
	else if (!getenv("OLDPWD"))
		ft_exit("NO OLDPWD", EXIT_FAILURE);
}

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

#include "minishell.h"

// Function to create the linked list from the environment variables
t_list_env *create_env_list(char **env)
{
    t_list_env *head = NULL;
    t_list_env *new = NULL;
    t_list_env *current = NULL;
    int i = 0;

    while (env[i])
    {
		new = (t_list_env *)calloc(1, sizeof(t_list_env));
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
    return head;
}

t_list_env *env_parse(char **env)
{
    t_list_env *head;

    head = create_env_list(env); // Call the new function to create the linked list
    head->path = get_path(getenv("PATH"));
    head->env = get_env(env);
    return head;
}
