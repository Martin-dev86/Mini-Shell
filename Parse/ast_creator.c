/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:57:35 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/06 17:48:37 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

// Create a new AST node
t_node *create_ast_node(t_token *operation, t_node *left, t_node *right)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (node == NULL) 
    {
        printf("Error: memory allocation failed\n");
        exit(1);
    }
    node->operation = operation;
    printf("Node content: %s\n", operation->read);
    node->left = left;
    node->right = right;
    node->n_childs = (left ? 1 : 0) + (right ? 1 : 0);
    return (node);
}

// Parse the factor and build the AST
// A factor is either a command or an argument
// !!!!!!!!!!!!!!!!!!!!!!!!!
// ARG is not implemented yet
t_node *parse_factor(t_list_token **current)
{
    t_node *node = NULL;
    if ((*current)->content->type == CMD || (*current)->content->type == ARG) 
    {
        node = create_ast_node((*current)->content, NULL, NULL);
        *current = (*current)->next;
    } 
    else 
    {
        printf("Syntax error: expected a command or argument\n");
        exit(1);
    }
    return (node);
}

// Parse the term and build the AST
// A term is a factor followed by zero or more redirections
t_node *parse_term(t_list_token **current) 
{
    t_node *node = parse_factor(current);
    while (*current && ((*current)->content->type == REDIR || (*current)->content->type == APPEND || (*current)->content->type == HEREDOC)) 
    {
        t_token *operation = (*current)->content;
        *current = (*current)->next;
        node = create_ast_node(operation, node, parse_factor(current));
    }
    return (node);
}

// Parse the expression and build the AST
// An expression is a term followed by zero or more pipes
t_node *parse_expression(t_list_token **current) 
{
    t_node *node = parse_term(current);
    while (*current && (*current)->content->type == PIPE) 
    {
        t_token *operation = (*current)->content;
        *current = (*current)->next;
        node = create_ast_node(operation, node, parse_term(current));
    }
    return (node);
}

// Main AST creator that returns the root node
t_node *ast_creator(t_list_token *token_list)
{
    t_node *ast;
    t_list_token *current = token_list;

    if (current == NULL)
        ft_exit("Empty\n", 1);

    ast = parse_expression(&current);

    return (ast);
}