/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:49:37 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 15:16:20 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Deterministic Finite Automaton
// It will do the sintax analysis of the tokens
// End state 0 is success and 1 is syntax error

int dfa_body(t_list_token *current, int state)
{
    //First start and state 1
    if (state == 0)
    {
        if (current == NULL)
            return (1);
        if (current->content->type == CMD)
            {
                state = 3;
                return (state);
            }
        if (current->content->type == REDIR || current->content->type == APPEND || current->content->type == HEREDOC)
            {
                state = 2;
                return (state);
            }
        else
            return (-1);
    }
    
    // State 2
    if (state == 2)
        {
            if(current->content->type == CMD)
                {
                    state = 3;
                    return (state);
                }
            else
                return (-1);
        }
    // State 3
    if (state == 3)
    {
        if (current->content->type == CMD)
            {
                state = 3;
                return (state);
            }
        if (current->content->type == REDIR || current->content->type == APPEND ||
            current->content->type == HEREDOC)
            {
                state = 2;
                return (state);
            }
        if (current->content->type == PIPE)
            {
                state = 4;
                return (state);
            }
        else
            return (-1);
    }

    // State 4
    if (state == 4)
    {
        if (current->content->type == CMD)
            {
                state = 3;
                return (state);
            }
        if (current->content->type == REDIR || current->content->type == APPEND ||
            current->content->type == HEREDOC)
            {
                state = 2;
                return (state);
            }
        else
            return (-1);
    }
    return (state);
}

// Final of the DFA

int dfa_main (t_list_token *token_list)
{
    t_list_token *head = token_list;
    t_list_token *current = head;
    
    int state = 0;
    // Start the DFA
    if (token_list == NULL)
        return (state);
    
    // Real DFA process REVIEW THIS
    while (current->next != NULL)
    {
        dfa_body(current, state);            
        current = current->next;
    }
    // Check the dfa final state
    return (state);
}
