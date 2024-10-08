/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:24:33 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 19:24:42 by jeandrad         ###   ########.fr       */
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
