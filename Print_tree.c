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
	if (node->type == N_IDENTIFIER)
	{
		printf(RED"%*s%s"GREEN""YELLOW"IDENTIFIER: \
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_REDIRECTION)
	{
		printf(RED"%*s%s"GREEN""YELLOW"REDIRECTION: \
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_COMMAND)
	{
		printf(RED"%*s%s"GREEN""YELLOW"COMMAND: \
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_ASSIGN)
	{
		printf(RED"%*s%s"GREEN""YELLOW"ASSIGNMENT: \
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_BUILTIN)
	{
		printf(RED"%*s%s"GREEN""YELLOW"BUILTIN: \
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_ARGUMENT)
	{
		printf(RED"%*s%s"GREEN""YELLOW"ARGUMENT:"\
		GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_DELIMITER)
	{
		printf(RED"%*s%s"GREEN""YELLOW"LIMITER:\
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_FILE)
	{
		printf(RED"%*s%s"GREEN""YELLOW"FILE:\
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_HEREDOC)
	{
		printf(RED"%*s%s"GREEN""YELLOW"HEREDOC:\
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(RED"%*s%s"GREEN""YELLOW"PIPELINE:\
		"GREEN" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
}

void	print_ast(t_ast *root)
{
	printf(GREEN"ARBOL\n");
	print_ast_helper(root, 0, "root: ");
}

void	print_assignment(t_assign *list)
{
	t_assign	*temp;
	int			i;

	i = 1;
	temp = list;
	if (!list)
		printf(BLUE"No assignments\n"GREEN);
	else
	{
		printf(BLUE"\nAssignment List\n"GREEN);
		while (temp)
		{
			printf("Node %d: Variable = %s, Value = \
			 %s\n", i, temp->variable, temp->value);
			temp = temp->next;
			i++;
		}
	}
}

void	print_list(t_idenlst *list)
{
	t_idenlst	*temp;
	int			i;

	i = 1;
	temp = list;
	if (!list)
		printf(BLUE"No list\n"GREEN);
	else
	{
		printf(BLUE"\nList\n"GREEN);
		while (temp)
		{
			printf("Node %d: Value = %s\n", i, temp->token->value);
			temp = temp->next;
			i++;
		}
	}
}*/