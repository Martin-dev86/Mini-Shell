/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/26 12:28:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will expand the string
void	exp_ast_helper(t_node *node, int depth)
{
	if (node == NULL)
		return ;
	else if (node->operation->type == CMD)
	{
		if (strcmp(node->operation->read, "pwd") == 0
			|| strcmp(node->operation->read, "echo") == 0
			|| strcmp(node->operation->read, "env") == 0
			|| strcmp(node->operation->read, "export") == 0
			|| strcmp(node->operation->read, "unset") == 0
			|| strcmp(node->operation->read, "cd") == 0)
		{
			node->operation->type = BUILTIN;
			exp_ast_helper(node->left, depth + 2);
			exp_ast_helper(node->right, depth + 2);
		}
	}
	else
	{
		exp_ast_helper(node->left, depth + 2);
		exp_ast_helper(node->right, depth + 2);
	}
}

t_node	*final_tree(t_node *root, t_list_env *env)
{
	(void)env;
	exp_ast_helper(root, 0);
	return (root);
}
