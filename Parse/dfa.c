/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:49:37 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/06 23:40:15 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

// Function to handle states 0 to 2
int dfa_body_part1(t_list_token *current, int state)
{
    if (state == 0)
    {
        if (current == NULL)
            return (1);
        if (current->content->type == CMD)
            return (3);
        if (current->content->type == REDIR_L
            || current->content->type == REDIR_R
            || current->content->type == APPEND
            || current->content->type == HEREDOC)
            return (2);
        else
            return (-1);
    }
    if (state == 2)
    {
        if (current->content->type == CMD)
            return (3);
        else
            return (-1);
    }
    return state;
}

// Function to handle states 3 to 4
int dfa_body_part2(t_list_token *current, int state)
{
    // State 3
    if (state == 3)
    {
        if (current->content->type == CMD)
            return (3);
        if (current->content->type == REDIR_L
            || current->content->type == REDIR_R
            || current->content->type == APPEND
            || current->content->type == HEREDOC)
            return (2);
        if (current->content->type == PIPE)
            return (4);
        else
            return (-1);
    }
    // State 4
    if (state == 4)
    {
        if (current->content->type == CMD)
            return (3);
        if (current->content->type == REDIR_L
            || current->content->type == REDIR_R
            || current->content->type == APPEND
            || current->content->type == HEREDOC)
            return (2);
        else
            return (-1);
    }
    return state;
}

// Main DFA function
int dfa_body(t_list_token *current, int state)
{
	if (state == -1)
		return -1;
    if (state >= 0 && state <= 2)
        return dfa_body_part1(current, state);
	if (state >= 3 && state <= 4)
        return dfa_body_part2(current, state);
    
    return (state);
}

// Final of the DFA
int dfa_main(t_list_token *token_list)
{
    t_list_token *head;
    t_list_token *current;
    int state;

    head = token_list;
    current = head;
    state = 0;
    if (token_list == NULL)
        return (0);
    while (current != NULL)
    {
        state = dfa_body(current, state);
        current = current->next;
    }
    current = head;
    return (state);
}
