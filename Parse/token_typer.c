/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/02 18:14:42 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// I create a list of tokens for the DFA
t_list_token *token_list(t_token *token)
{
    t_list_token *new;
    t_list_token *head;
    
    new = (t_list_token *)malloc(sizeof(t_list_token));
    if (!new)
        exit(1);
    head = new;
    new->content = token;
    new->next = NULL;
    return (head);
}

// This function will determine the type of token
void token_typer (t_token *token)
{    
	int	i;

	i = 0;
	token->len = 0;
    while(token->argument[i])
    {	
		i++;
		token->len += 1;
	}
	i = 0;
    while(i < token->len)
	{	
		if (ft_strcmp(token->argument[i], "|") == 0)
			token->type = PIPE;
		if (ft_strcmp(token->argument[i], ">") == 0)
			token->type = REDIR;
		if (ft_strcmp(token->argument[i], "<") == 0)
			token->type = REDIR;
		if (ft_strcmp(token->argument[i], ">>") == 0)
			token->type = APPEND;
		if (ft_strcmp(token->argument[i], "<<") == 0)
			token->type = HEREDOC;
		if (ft_strcmp(token->argument[i], "\n") == 0)
			token->type = ENDLINE;
		else
			token->type = BUILTIN;
		i++;
	}
}
