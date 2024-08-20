/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:49:37 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/20 10:20:39 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser_dfa (t_token *token)
{
    if (token->content == '|')
        token->type = PIPE;
    else if (token->content == '>')
        token->type = REDIR;
    else if (token->content == '<')
        token->type = REDIR;
    else if (token->content == '>>')
        token->type = APPEND;
    else if (token->content == '<<')
        token->type = HEREDOC;
    else if (token->content == '\n')
        token->type = ENDLINE;
    else
        token->type = CMD;
}

void states_dfa (t_token *token)
