/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:57:35 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 10:32:49 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (current->content->priority < \
		highest_priority_token->content->priority)
			highest_priority_token = current;
		current = current->next;
	}
	return (highest_priority_token);
}

// Function to handle pipe token type
void	handle_pipe(t_node *node, t_list_token *highest_priority_token,
		t_list_token *start, t_list_token *end)
{
	if (highest_priority_token->prev != NULL)
		node->left = ast_creator(start, highest_priority_token->prev);
	if (highest_priority_token->next != NULL)
		node->right = ast_creator(highest_priority_token->next, end);
}

// Function to handle redirection and command token types
void	handle_redir_cmd(t_node *node, t_list_token *highest_priority_token,
		t_list_token *start)
{
	if (highest_priority_token->prev != NULL)
		node->left = ast_creator(start, highest_priority_token->prev);
	if (highest_priority_token->next != NULL)
	{
		if (highest_priority_token->content->type == HEREDOC)
			node->right = \
			create_ast_node(highest_priority_token->next->content);
		else
			node->right = \
			create_ast_node(highest_priority_token->next->content);
	}
}

// Modified function to handle different token types
void	handle_token_type(t_node *node, t_list_token *highest_priority_token,
		t_list_token *start, t_list_token *end)
{
	if (highest_priority_token->content->type == PIPE)
		handle_pipe(node, highest_priority_token, start, end);
	else if (highest_priority_token->content->type == REDIR_L
		|| highest_priority_token->content->type == REDIR_R
		|| highest_priority_token->content->type == APPEND
		|| highest_priority_token->content->type == HEREDOC)
		handle_redir_cmd(node, highest_priority_token, start);
	else if (highest_priority_token->content->type == CMD
		|| highest_priority_token->content->type == ARG)
	{
		if (highest_priority_token->next != NULL)
			node->right = ast_creator(highest_priority_token->next, end);
		if (highest_priority_token->prev != NULL)
			node->left = ast_creator(start, highest_priority_token->prev);
	}
}

// Recursive function to build the AST
t_node	*ast_creator(t_list_token *start, t_list_token *end)
{
	t_list_token	*highest_priority_token;
	t_node			*node;
	//t_list_token	*head;

	//head = start;
	if (start == NULL || start == end->next)
		return (NULL);
	highest_priority_token = find_highest_priority_token(start,
			end);
	node = create_ast_node(highest_priority_token->content);
	handle_token_type(node, highest_priority_token, start, end);
	//free_token_list(head);
	return (node);
}
