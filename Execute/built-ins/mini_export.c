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

int	mini_export(t_list_env *env, t_token *token)
{
	t_list_env	*promp;
	t_list_env	*current;
	char		*temp;
	int			i;

	i = 0;
	while (token->read[i])
		i++;
	if (i == 1)
	{
		while (current)
		{
			if (ft_strcmp(current->content, current->next->content) < 0)
			{
				temp = current->next->content;
				current->next->content = current->content;
				current->content = temp;
			}
			current = current->next;
		}
		i = mini_env(env);
	}
	promp = mini_lstnew(token->argument[1]);
	mini_lstadd_back(env, promp);
	return (0);
}
