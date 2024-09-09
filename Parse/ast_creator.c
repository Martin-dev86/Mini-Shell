/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:57:35 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/09 11:15:21 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Helper function to create a new AST node
t_node *create_ast_node(t_token *operation) {
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    node->operation = operation;
    node->left = NULL;
    node->right = NULL;
    node->n_childs = 0;
    return node;
}

// Function to find the index of the highest-priority token in the token list
int find_highest_priority_token(t_token **tokens, int start, int end) {
    int i;
    int highest_priority_index = start;
    for (i = start; i <= end; i++) {
        if (tokens[i]->priority < tokens[highest_priority_index]->priority) {
            highest_priority_index = i;
        }
    }
    return highest_priority_index;
}

// Recursive function to build the AST
t_node *ast_creator(t_token *token, int start, int end) 
{
    if (start > end) {
        return NULL;
    }
    // Find the token with the highest priority (pipes first, then redirections)
    int highest_priority_index = find_highest_priority_token(tokens, start, end);
    // Create a node for the highest-priority token
    t_node *node = create_ast_node(tokens[highest_priority_index]);
    // If the token is a pipe, its children are commands or other pipes
    if (tokens[highest_priority_index]->type == PIPE) {
        node->left = ast_creator(tokens, start, highest_priority_index - 1);
        node->right = ast_creator(tokens, highest_priority_index + 1, end);
    }
    // If the token is a redirection, attach it to the appropriate command node
    else if (tokens[highest_priority_index]->type == REDIR ||
             tokens[highest_priority_index]->type == APPEND) {
        // Redirection affects the right side (file), so left is the command, right is the file
        node->left = ast_creator(tokens, start, highest_priority_index - 1);
        node->right = ast_creator(tokens, highest_priority_index + 1, end);
    }
    // If it's a command or argument, there may be more tokens to process in a sequential order
    else if (tokens[highest_priority_index]->type == CMD || tokens[highest_priority_index]->type == ARG) {
        node->left = ast_creator(tokens, start, highest_priority_index - 1);
        node->right = ast_creator(tokens, highest_priority_index + 1, end);
    }
    return node;
}

t_node *final_ast_creator(t_list_token *tokens, int start, int end)
{
    t_node *root;
    
    t_list_token *head = tokens;
    while (tokens)
    {
        root = ft_calloc(0, sizeof(t_node));
        root = ast_creator(tokens->content, start, end);
        tokens = tokens->next;
    }
    tokens = head;
    return (root);
}