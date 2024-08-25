/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:49:37 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/23 19:47:39 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Deterministic Finite Automaton
// It will do the sintax analysis of the tokens

// !!!!!!!!
// FIXME: This is a draft, it needs to be reviewed
// !!!!!!!!
int dfa_main (t_list_token *token_list)
{
¡   t_list_token *head = token_list;
    t_list_token *current = head;
    t_list_token *next = head->next;
    int state = 0;

    // Start the DFA
    if (token_list == NULL)
        return (state);
    
    // Real DFA process REVIEW THIS
    while (current->next)
    {
        if (current->content->type == CMD)
        {
            state = 0;
            if (next->content->type == PIPE)
            {
                state = 1;
                current->content->type = PIPE;
                current->content->priority = 1;
            }
            else if (next->content->type == REDIR)
            {
                // state
                current->content->type = REDIR;
                current->content->priority = 2;
            }
            else if (next->content->type == APPEND)
            {
                state = 1;
                current->content->type = APPEND;
                current->content->priority = 2;
            }
            else if (next->content->type == HEREDOC)
            {
                // state
                current->content->type = HEREDOC;
                current->content->priority = 2;
            }
            else if (next->content->type == ENDLINE)
            {
                state = 0;
                current->content->type = ENDLINE;
                current->content->priority = 3;
            }
            else
            {
                state = 0;
                current->content->type = CMD;
                current->content->priority = 0;
            }
        }
        current = current->next;
        next = current->next;
    }
    return (state);
}