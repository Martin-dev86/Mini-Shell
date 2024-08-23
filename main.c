/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/23 00:05:43 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// t_node	*create_node(t_token *operation, t_node *left_content, t_node *right_content)
// {
// 	t_node	*node;

// 	node = malloc(sizeof(t_node));
// 	if (!node)
// 	{
// 		perror("Failed to allocate memory for node");
// 		exit(EXIT_FAILURE);
// 	}
// 	node->operation = operation;
// 	node->left = left_content;
// 	node->right = right_content;
// 	node->n_childs = (left_content ? 1 : 0) + (right_content ? 1 : 0);
// 	return (node);
// }

// t_token	*create_token(char *operation, t_type type) 
// {
// 	t_token	*token;

// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 	{
// 		perror("Failed to allocate memory for token");
// 		exit(EXIT_FAILURE);
// 	}
// 	//token->argument[1] = operation;
// 	token->type = type;

// 	return (token);
// }

// t_node	*make_tree(void)
// {
// 	t_token	*pwd;
// 	t_token	*redirect_token;
// 	t_token	*output_token;
// 	t_node	*output_node;
// 	t_node	*pwd_node;
// 	t_node	*redirect_node;

// 	redirect_token = create_token(">", REDIR);
// 	pwd = create_token("pwd", BUILTIN);
// 	output_token = create_token("output.txt", FILE_PATH);
// 	output_node = create_node(output_token, NULL, NULL);
// 	redirect_node = create_node(redirect_token, NULL, output_node);
// 	pwd_node = create_node(pwd, redirect_node, NULL);
// 	return (pwd_node);
// }

int	main(int argc, char **argv, char **env)
{
	t_token	*token;
	t_son	*son;
	int		i;
	
	i = 0;
	(void)argc;
	(void)argv;
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
		token->argument = (char **)malloc((i + 1) * sizeof(char *));
    	if (!token->argument)
		{
        	perror("Error al asignar memoria");
        	exit(EXIT_FAILURE);
		}
		token->read = readline("Minishell>");
		if (token->read == NULL || ft_strcmp(token->read, "exit") == 0)
			break ;
		while(token->argument[i])
			i++;
		token->argument = ft_split(token->read, ' ');
		token_typer(token);
		//pwd_node = make_tree();
		//print_ast(pwd_node);
		execute(token, son, env);
		add_history(token->read);
	}
	return (0);
}
