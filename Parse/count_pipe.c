/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:39:29 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/13 17:39:47 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function to recursively count "pipe" tokens
void count_pipe_tokens_helper(t_node *node, int *counter)
{
    if (node == NULL)
        return ;

    if (node->operation != NULL && node->operation->read != NULL &&
        strcmp(node->operation->read, "|") == 0)
        (*counter)++;

    count_pipe_tokens_helper(node->left, counter);
    count_pipe_tokens_helper(node->right, counter);
}

// Function to count the number of tokens with content equal to "pipe"
int count_pipe_tokens(t_node *root) 
{
    // There must be at least one son process
    int counter = 1;
    t_node *head = root;

    count_pipe_tokens_helper(root, &counter);
    root = head;
    return (counter);
}