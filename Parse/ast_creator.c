/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:57:35 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/27 20:30:13 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to create a new AST node
t_node	*create_ast_node(t_token *operation)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	node->operation = operation;
	node->left = NULL;
	node->right = NULL;
	node->n_childs = 0;
	return (node);
}

// Function to find the highest-priority token in the token list
t_list_token	*find_highest_priority_token(t_list_token *start,
		t_list_token *end)
{
	t_list_token	*current;
	t_list_token	*highest_priority_token;

	current = start;
	highest_priority_token = start;
	while (current != end->next)
	{
		if (current->content->priority < highest_priority_token->content->priority)
		{
			highest_priority_token = current;
		}
		current = current->next;
	}
	return (highest_priority_token);
}

// Recursive function to build the AST
t_node	*ast_creator(t_list_token *start, t_list_token *end)
{
	if (start == NULL || start == end->next)
		return (NULL);
	// Find the token with the highest priority (pipes first, then redirections)
	t_list_token *highest_priority_token = find_highest_priority_token(start,
			end);
	// Create a node for the highest-priority token
	t_node *node = create_ast_node(highest_priority_token->content);
	// If the token is a pipe, its children are commands or other pipes
	if (highest_priority_token->content->type == PIPE)
	{
		if (highest_priority_token->prev != NULL)
			node->left = ast_creator(start, highest_priority_token->prev);
		if (highest_priority_token->next != NULL)
			node->right = ast_creator(highest_priority_token->next, end);
	}
	// If the token is a redirection, attach it to the appropriate command node
	else if (highest_priority_token->content->type == REDIR_L
		|| highest_priority_token->content->type == REDIR_R
		|| highest_priority_token->content->type == APPEND)
	{
		// Redirection affects the right side (file), so left is the command,
		//	right is the file
		if (highest_priority_token->prev != NULL)
		{
			printf("Creating left node\n");
			node->left = ast_creator(start, highest_priority_token->prev);
			//node->left->right = node; // Attach the redirection to the command
		}
		if (highest_priority_token->next != NULL)
		{
			printf("Creating right node\n");
			node->right = create_ast_node(highest_priority_token->next->content);
		}
	}
	// If it's a command or argument,
	//	there may be more tokens to process in a sequential order
	else if (highest_priority_token->content->type == CMD
		|| highest_priority_token->content->type == ARG)
	{
		if (highest_priority_token->prev != NULL )
			node->right = ast_creator(start, highest_priority_token->prev);

		if (highest_priority_token->next != NULL)
			node->left = ast_creator(highest_priority_token->next, end);
	}
	return (node);
}