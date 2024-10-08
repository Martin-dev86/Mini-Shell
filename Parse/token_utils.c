/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:20:37 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 19:20:45 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prev_pointers(t_list_token *head)
{
	t_list_token	*current;
	t_list_token	*prev;

	current = head;
	prev = NULL;
	while (current != NULL)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}
