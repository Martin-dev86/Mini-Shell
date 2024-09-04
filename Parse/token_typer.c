/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 17:23:26 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// This function will determine the type of token_list
void token_list_typer (t_list_token *token_list)
{    
	t_list_token * head;

	head = token_list;
    while(token_list->next != NULL)
	{	
		if (ft_strcmp(token_list->content->read, "|") == 0)
			token_list->content->type = PIPE;
		else if (ft_strcmp(token_list->content->read, ">") == 0)
			token_list->content->type = REDIR;
		else if (ft_strcmp(token_list->content->read, "<") == 0)
			token_list->content->type = REDIR;
		else if (ft_strcmp(token_list->content->read, ">>") == 0)
			token_list->content->type = APPEND;
		else if (ft_strcmp(token_list->content->read, "<<") == 0)
			token_list->content->type = HEREDOC;
		else if (ft_strcmp(token_list->content->read, "\n") == 0)
			token_list->content->type = ENDLINE;
		else
			token_list->content->type = CMD;
		token_list = token_list->next;
	}
	token_list = head;
}
