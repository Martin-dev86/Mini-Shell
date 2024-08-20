/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 13:19:03 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// Function to create new AST node
t_node *create_node(t_token *operation, t_node *left_content, t_node *right_content) 
{
    t_node *node = malloc(sizeof(t_node));
    if (!node) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->operation = operation;
    node->left_content = left_content;
    node->right_content = right_content;
    node->n_childs = (left_content ? 1 : 0) + (right_content ? 1 : 0);
    return node;
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token;

	(void)argc;
	(void)argv;
	while (1)
	{
		token = calloc(1, sizeof(t_token));
		if (!token)
		{
			perror("Failed to allocate memory for token");
			exit(EXIT_FAILURE);
		}
		token->content = readline("Minishell>");
		if (token->content == NULL || ft_strcmp(token->content, "exit") == 0)
			break;
		printf("\n\ntoken->content = %s\n\n", token->content);
		token_maker(token, env);

		// AST creation for the command `echo "Hello, World!" > output.txt` to test execute function
		t_token *echo = create_token("echo",BUILTIN, NULL);
		t_token *hello_token = create_token("\"Hello, World!\"", ARG, NULL);
		t_token *redirect_token = create_token(">", REDIR, 0);
		t_token *output_token = create_token("output.txt", FILE_PATH, 0);
		t_node *output_node = create_node(output_token, NULL, NULL);
		t_node *redirect_node = create_node(redirect_token, NULL, output_node);
		t_node *hello_node = create_node(hello_token, NULL, NULL);
		t_node *echo_node = create_node(echo, hello_node, redirect_node);

		// Assuming execute is a function that takes a t_node and a char*
		execute(echo_node, token->content);
		add_history(token->content);
	}
	return 0;
}

	// char	*content;

	// (void)argc;
	// (void)argv;
	// (void)env;
	// while (1)
	// {
	// 	content = readline("Minishell>");
	// 	if (content == NULL || ft_strcmp(content, "exit") == 0)
	// 		break ;

	// 	if (ft_strcmp(content, "pwd") == 0)
	// 		printf("%s\n", ft_get_pwd());
	// 	add_history(content);
	// }
	// return (0);
void	print_ast_helper(t_ast *node, int depth, char *side)
{
	if (node == NULL)
		return ;
	if (node->type == N_IDENTIFIER)
	{
		printf(RED"%*s%s"RESET""YELLOW"IDENTIFIER: \
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_REDIRECTION)
	{
		printf(RED"%*s%s"RESET""YELLOW"REDIRECTION: \
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_COMMAND)
	{
		printf(RED"%*s%s"RESET""YELLOW"COMMAND: \
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_ASSIGN)
	{
		printf(RED"%*s%s"RESET""YELLOW"ASSIGNMENT: \
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_BUILTIN)
	{
		printf(RED"%*s%s"RESET""YELLOW"BUILTIN: \
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_ARGUMENT)
	{
		printf(RED"%*s%s"RESET""YELLOW"ARGUMENT:"\
		RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_DELIMITER)
	{
		printf(RED"%*s%s"RESET""YELLOW"LIMITER:\
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_FILE)
	{
		printf(RED"%*s%s"RESET""YELLOW"FILE:\
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_HEREDOC)
	{
		printf(RED"%*s%s"RESET""YELLOW"HEREDOC:\
		"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(RED"%*s%s"RESET""YELLOW"PIPELINE:\
		"RESET" %s\n", depth * 2, "", side, node->token->value);
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
		printf(BLUE"No assignments\n"RESET);
	else
	{
		printf(BLUE"\nAssignment List\n"RESET);
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
		printf(BLUE"No list\n"RESET);
	else
	{
		printf(BLUE"\nList\n"RESET);
		while (temp)
		{
			printf("Node %d: Value = %s\n", i, temp->token->value);
			temp = temp->next;
			i++;
		}
	}
}*/