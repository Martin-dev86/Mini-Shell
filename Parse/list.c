/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:26:29 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/04 18:06:48 by cagarci2         ###   ########.fr       */
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
