/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/21 13:18:45 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// Function to create new AST node
t_node	*create_node(t_token *operation, t_node *left_content, t_node *right_content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		perror("Failed to allocate memory for node");
		exit(EXIT_FAILURE);
	}
	node->operation = operation;
	node->left = left_content;
	node->right = right_content;
	node->n_childs = (left_content ? 1 : 0) + (right_content ? 1 : 0);
	return (node);
}

t_token	*create_token(char *operation, t_type type) 
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("Failed to allocate memory for token");
		exit(EXIT_FAILURE);
	}
	token->content = operation;
	token->type = type;

	return (token);
}

t_node	*make_tree(void)
{
	t_token	*pwd;
	t_token	*redirect_token;
	t_token	*output_token;
	t_node	*output_node;
	t_node	*pwd_node;
	t_node	*redirect_node;

	redirect_token = create_token(">", REDIR);
	pwd = create_token("pwd", BUILTIN);
	output_token = create_token("output.txt", FILE_PATH);
	output_node = create_node(output_token, NULL, NULL);
	redirect_node = create_node(redirect_token, NULL, output_node);
	pwd_node = create_node(pwd, redirect_node, NULL);
	return (pwd_node);
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token;
	t_son	*son;
	//t_node	*pwd_node;

	(void)argc;
	(void)argv;
	(void)env;
	son = malloc(sizeof(t_son));
	if (son == NULL)
	{
		perror ("malloc");
		exit (1);
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
			break ;
		if (ft_strcmp(token->content, "pwd") == 0)
			token->type = BUILTIN;
		if (ft_strcmp(token->content, "echo") == 0)
			token->type = BUILTIN;
		//pwd_node = make_tree();
		//print_ast(pwd_node);
		execute(token, son);
		add_history(token->content);
	}
	return (0);
}
