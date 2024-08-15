/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/15 19:06:01 by jeandrad         ###   ########.fr       */
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

int main(int argc, char **argv, char **env)
{
    t_token *token;

    (void)argc;
    (void)argv;
    while (1)
    {
        token = calloc(1, sizeof(t_token));
        if (!token) {
            perror("Failed to allocate memory for token");
            exit(EXIT_FAILURE);
        }
        token->content = readline("Minishell>");
        if (token->content == NULL || ft_strcmp(token->content, "exit") == 0)
            break;
        printf("\n\ntoken->content = %s\n\n", token->content);
        token_maker(token, env);

        // AST creation for the command `echo "Hello, World!" > output.txt` to test execute function
        t_token *echo = create_token("echo",CMD, NULL);
        t_token *hello_token = create_token("\"Hello, World!\"", ARG, NULL);
        t_token *redirect_token = create_token(">", FILE_PATH, 0);
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
