/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 18:01:27 by cagarci2         ###   ########.fr       */
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
	t_son	*son;
	(void)argc;
	(void)argv;
	(void)env;
	son = malloc(sizeof(t_son));
	if (son == NULL)
	{
    	perror("malloc");
    	exit(1);
	}
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
		if (ft_strcmp(token->content, "pwd") == 0)
			token->type = BUILTIN;
		// token_maker(token, env);
		// AST creation for the command `echo "Hello, World!" > output.txt` to test execute function
		//t_token *pwd = create_token("pwd", BUILTIN, NULL);
		// t_token *hello_token = create_token("\"Hello, World!\"", ARG, NULL);
		// t_token *redirect_token = create_token(">", REDIR, 0);
		// t_token *output_token = create_token("output.txt", FILE_PATH, 0);
		// t_node *output_node = create_node(output_token, NULL, NULL);
		// t_node *redirect_node = create_node(redirect_token, NULL, output_node);
		// t_node *hello_node = create_node(hello_token, NULL, NULL);
		// t_node *echo_node = create_node(echo, hello_node, redirect_node);
		// Assuming execute is a function that takes a t_node and a char*
		//execute(echo_node, token->content);
		execute(token, son);
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