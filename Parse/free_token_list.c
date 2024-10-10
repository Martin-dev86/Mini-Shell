/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:10:36 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 18:11:31 by jeandrad         ###   ########.fr       */
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
		printf("freeing content->read: %s\n", content->read);
		free(content->read);
		content->read = NULL;
	}
	if (content->path)
	{
		printf("freeing content->path: %s\n", content->path);
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
		printf("passes through free_token_list to free current\n");
		current = next;
	}
	start = NULL;
}

// Free the doubly linked list of tokens without freeing the content (t_token)
void	free_token_list_without_content(t_list_token *start)
{
	t_list_token	*current;
	t_list_token	*next;

	if (start == NULL)
		return ;
	current = start;
	while (current != NULL)
	{
		next = current->next;

		free(current);
		current = next;
	}
	start = NULL;
}
