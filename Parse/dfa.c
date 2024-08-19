/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:49:37 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/19 19:54:07 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser_dfa (t_token *token)
{
    if (token->content == ' ')
        token->type = ARG;
    else if (token->content == '|')
        token->type = PIPE;
    else if (token->content == ';')
        token->type = SEMICOLON;
    else if (token->content == '>')
        token->type = REDIR;
    else if (token->content == '<')
        token->type = HEREDOC;
    else if (token->content == '(' || token->content == ')')
        token->type = PARENTHESIS;
    else if (token->content == '\n')
        token->type = ENDLINE;
    else
        token->type = CMD;
}

void states_dfa (t_token *token)
