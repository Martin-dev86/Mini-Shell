/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:10:36 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 18:42:15 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
