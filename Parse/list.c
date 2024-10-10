/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:26:29 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/10 16:46:55 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*mini_lstnew(void *content)
{
	t_list_env	*new;

	new = ft_calloc(1, sizeof(t_list_env));
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

void	mini_lstadd_back(t_list_env **lst, t_list_env *new)
{
	t_list_env	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = mini_lstlast(*lst);
		last->next = new;
	}
}

int	mini_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '=')
		i++;
	i++;
	return (i);
}
