/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:43 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:46:43 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '=')
		i++;
	return (i);
}
t_list_env	*mini_lstnew(void *content)
{
	t_list_env	*new;

	new = (t_list_env *) malloc(sizeof(t_list_env));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list_env	*mini_lstlast(t_list_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	mini_lstadd_back(t_list_env *lst, t_list_env *new)
{
	t_list_env	*last;

	if (lst && new)
	{
		if (!lst)
			lst = new;
		else
		{
			last = mini_lstlast(lst);
			last->next = new;
		}
	}
}
t_list_env	*mini_sort(t_list_env *current)	
{
	t_list_env	*new_node;
	t_list_env	*sorted_env;

	sorted_env = NULL;
	while (current)
	{
		new_node = mini_lstnew(ft_strdup(current->content));
		mini_lstadd_back(sorted_env, new_node);
		current = current->next;
	}
	return(sorted_env); 
}

int	mini_export(t_list_env *env, t_token *token)
{
	t_list_env	*promp;
	t_list_env	*current;
	t_list_env	*sorted_current;
	char		*temp;
	size_t		j;
	int			swapped;
	int			i;

	i = 0;
	while (token->argument[i])
		i++;
	if (i == 1)
	{
		current = env;
		swapped = 1;
		while (swapped)
		{
			swapped = 0;
			sorted_current = mini_sort(current);
			while (current && current->next)
			{
				j = mini_strlen(current->content);
				if (ft_strncmp(current->content, current->next->content, j) > 0)
				{
					temp = current->content;
					current->content = current->next->content;
					current->next->content = temp;
					swapped = 1;
				}
				current = current->next;
			}
		}
		current = sorted_current;
	while(current && current->next)
	{	
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
		return (0);
	}
	promp = mini_lstnew(token->argument[1]);
	mini_lstadd_back(env, promp);
	return (0);
}
