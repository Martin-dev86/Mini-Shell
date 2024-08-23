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

int dfa_main (t_token *token)
{
    
}

// I create a list of tokens for the DFA
t_list token_list (t_token *token)
{
    t_list list;
    t_list *new;
    int i;

    i = 0;
    list = NULL;
    while (token->argument[i])
    {
        new = (t_list *)malloc(sizeof(t_list));
        if (!new)
            exit(1);
        new->content = token->argument[i];
        new->next = list;
        list = new;
        i++;
    }
    return (list);
}