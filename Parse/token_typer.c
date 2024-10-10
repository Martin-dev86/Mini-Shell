/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 19:10:48 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to set the type and priority of a token
void	set_token_type(t_list_token *token)
{
	if (ft_strcmp(token->content->read, "|") == 0)
	{
		token->content->type = PIPE;
		token->content->priority = 1;
	}
	else if (ft_strcmp(token->content->read, "\n") == 0)
	{
		token->content->type = ENDLINE;
		token->content->priority = 2;
	}
	else
	{
		token->content->type = CMD;
		token->content->priority = 3;
	}
}

// Function to handle redirection tokens
void	handle_1_redir(t_list_token **token_list)
{
	if (ft_strcmp((*token_list)->content->read, ">") == 0)
	{
		(*token_list)->content->type = REDIR_R;
		(*token_list)->content->priority = 2;
	}
	else if (ft_strcmp((*token_list)->content->read, "<") == 0)
	{
		(*token_list)->content->type = REDIR_L;
		(*token_list)->content->priority = 2;
	}
	*token_list = (*token_list)->next;
	if (*token_list)
	{
		(*token_list)->content->type = CMD;
		(*token_list)->content->priority = 3;
	}
}

void	handle_2_redir(t_list_token **token_list)
{
	if (ft_strcmp((*token_list)->content->read, ">>") == 0)
	{
		(*token_list)->content->type = APPEND;
		(*token_list)->content->priority = 2;
	}
	else if (ft_strcmp((*token_list)->content->read, "<<") == 0)
	{
		(*token_list)->content->type = HEREDOC;
		(*token_list)->content->priority = 2;
	}
	*token_list = (*token_list)->next;
	if (*token_list)
	{
		(*token_list)->content->type = CMD;
		(*token_list)->content->priority = 3;
	}
}

// Main function to determine the type of token_list
void	token_list_typer(t_list_token *token_list)
{
	t_list_token	*head;

	head = token_list;
	while (token_list)
	{
		if (ft_strcmp(token_list->content->read, "|") == 0)
			set_token_type(token_list);
		else if (ft_strcmp(token_list->content->read, ">") == 0
			|| ft_strcmp(token_list->content->read, "<") == 0)
		{
			handle_1_redir(&token_list);
			continue ;
		}
		else if (ft_strcmp(token_list->content->read, ">>") == 0
			|| ft_strcmp(token_list->content->read, "<<") == 0)
		{
			handle_2_redir(&token_list);
			continue ;
		}
		else
			set_token_type(token_list);
		token_list = token_list->next;
	}
	token_list = head;
}
