/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/03 22:40:36 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will determine the type of token_list
void	token_list_typer(t_list_token *token_list)
{
	t_list_token	*head;
	//int				i;

	head = token_list;
	//i = 0;
	//printf("Entering token_list_typer\n");
	while (token_list)
	{
		//printf("i: %d\n", i++);
		if (ft_strcmp(token_list->content->read, "|") == 0)
		{
			token_list->content->type = PIPE;
			token_list->content->priority = 1;
		}
		else if (ft_strcmp(token_list->content->read, ">") == 0)
		{
			token_list->content->type = REDIR_R;
			token_list->content->priority = 2;
			token_list = token_list->next;
			token_list->content->type = CMD;
			token_list->content->priority = 3;
		}
		else if (ft_strcmp(token_list->content->read, "<") == 0)
		{
			token_list->content->type = REDIR_L;
			token_list->content->priority = 2;
			token_list = token_list->next;
			token_list->content->type = CMD;
			token_list->content->priority = 3;
		}
		else if (ft_strcmp(token_list->content->read, ">>") == 0)
		{
			token_list->content->type = APPEND;
			token_list->content->priority = 2;
			token_list = token_list->next;
			token_list->content->type = CMD;
			token_list->content->priority = 3;
		}
		else if (ft_strcmp(token_list->content->read, "<<") == 0)
		{
			token_list->content->type = HEREDOC;
			token_list->content->priority = 2;
			token_list = token_list->next;
			token_list->content->type = CMD;
			token_list->content->priority = 3;
		}
		else if (ft_strcmp(token_list->content->read, "\n") == 0)
		{
			token_list->content->type = ENDLINE;
			token_list->content->priority = 2;
		}
		else
		{
			token_list->content->type = CMD;
			token_list->content->priority = 3;
			// Possible solution to the redirections problem
		}
		if (token_list)
			token_list = token_list->next;
	}
	//printf("Exiting token_list_typer\n");
	token_list = head;
}
