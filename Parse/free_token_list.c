/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:10:36 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 17:03:09 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free the content of a t_token structure
void	free_token_content(t_token *content)
{
	if (content == NULL)
		return ;
	if (content->read)
	{
		free(content->read);
		content->read = NULL;
	}
	if (content->path)
	{
		free(content->path);
		content->path = NULL;
	}
	free(content);
	content = NULL;
}

// Free a doubly linked list of tokens
void	free_token_list(t_list_token *start)
{
	t_list_token	*current;
	t_list_token	*next;

	if (start == NULL)
		return ;
	current = start;
	while (current != NULL)
	{
		next = current->next;
		if (current->content)
		{
			free_token_content(current->content);
			current->content = NULL;
		}
		free(current);
		current = next;
	}
	start = NULL;
}
