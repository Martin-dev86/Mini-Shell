/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/23 19:45:01 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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