/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:31:55 by cagarci2          #+#    #+#             */
/*   Updated: 2023/11/14 13:33:26 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;
	void	*con;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		con = f(lst->content);
		if (!con)
			break ;
		aux = ft_lstnew(con);
		if (!aux)
			break ;
		ft_lstadd_back(&new, aux);
		lst = lst->next;
	}
	if (lst)
	{
		ft_lstclear(&new, del);
		del(con);
		return (NULL);
	}
	return (new);
}
