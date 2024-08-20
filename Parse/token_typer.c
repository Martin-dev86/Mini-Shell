/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/20 17:41:18 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gives the type to the token after the token split
void token_typer (t_token *token)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(token->content[i])  
    {
        if (token->content[i] == '|')
            token->type = PIPE;
        else if (token->content[i] == '>')
            token->type = REDIR;
        else if (token->content[i] == '<')
            token->type = REDIR;
        else if (token->content[i] == '>>')
            token->type = APPEND;
        else if (token->content[i] == '<<')
            token->type = HEREDOC;
        else if (token->content[i] == '\n')
            token->type = ENDLINE;
        else
            token->type = BUILTIN;
    }   
}