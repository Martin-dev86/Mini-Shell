/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:28:18 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 16:28:18 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast_helper(t_node *node, int depth, char *side)
{
	if (node == NULL)
		return ;
	if (node->operation->type == CMD)
	{
		printf(RED"%*s%s"RESET""YELLOW"IDENTIFIER: "RESET" %s\n", depth * 2, \
            "", side, node->operation->read);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->operation->type == REDIR_L || node->operation->type == REDIR_R)
	{
		printf(RED"%*s%s"RESET""YELLOW"REDIRECTION: "RESET" %s\n", depth * 2, \
            "", side, node->operation->read);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->operation->type == BUILTIN)
	{
		printf(RED"%*s%s"RESET""YELLOW"BUILTIN: "RESET" %s\n", depth * 2, \
            "", side, node->operation->read);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(RED"%*s%s"RESET""YELLOW"PIPELINE: "RESET" %s\n",\
            depth * 2, "", side, node->operation->read);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
}

void	print_ast(t_node *root)
{
	printf(GREEN"\n\nARBOL\n");
	print_ast_helper(root, 0, "root: ");
}
