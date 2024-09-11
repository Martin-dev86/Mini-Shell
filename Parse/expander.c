/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/11 20:03:00 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Assuming the definitions of t_node, t_list_env, CMD, BUILTIN, and ft_calloc are available

// This function will expand the string
t_node *expand_string(t_node *ast, t_list_env *env)
{
    (void) env;
    if (ast->operation->type == CMD)
    {
        if (ast->operation->read[0] == '$')
        {
            // This will expand the string
            // This will return the string expanded
            return (ast);
        }
        else if (strcmp(ast->operation->read, "pwd") == 0)
            ast->operation->type = BUILTIN;
        else if (strcmp(ast->operation->read, "echo") == 0)
            ast->operation->type = BUILTIN;
        else if (strcmp(ast->operation->read, "cd") == 0)
            ast->operation->type = BUILTIN;
        else if (strcmp(ast->operation->read, "export") == 0)
            ast->operation->type = BUILTIN;
        else if (strcmp(ast->operation->read, "unset") == 0)
            ast->operation->type = BUILTIN;
        else if (strcmp(ast->operation->read, "env") == 0)
            ast->operation->type = BUILTIN;
        else if (strcmp(ast->operation->read, "exit") == 0)
            ast->operation->type = BUILTIN;
        else
            return (ast);
    }
    else
        return (ast);
    return (ast);    
}

// Helper function to print the tree
void print_tree(t_node *ast)
{
    if (ast == NULL)
        return;

    printf("Operation: %s, Type: %d\n", ast->operation->read, ast->operation->type);
    print_tree(ast->left);
    print_tree(ast->right);
}

// This function will expand the tree
// This returns the final tree to take to the executor
t_node *final_tree(t_node *ast, t_list_env *env)
{
    if (ast == NULL)
        return NULL;

    t_node *new = (t_node *)ft_calloc(1, sizeof(t_node));
    if (!new)
    {
        perror("Failed to allocate memory");
        exit(1);
    }

    t_node *head = new;

    // Traverse the tree and change types to BUILTIN where applicable
    while (ast != NULL)
    {
        new->operation = ast->operation;
        new = expand_string(ast, env); // This will change the type to BUILTIN if applicable

        printf("Operation: %s, Type: %d\n", new->operation->read, new->operation->type);
        if (ast->left != NULL)
        {
            new->left = (t_node *)ft_calloc(1, sizeof(t_node));
            if (!new->left)
            {
                perror("Failed to allocate memory");
                exit(1);
            }
            new = new->left;
            ast = ast->left;
        }
        else if (ast->right != NULL)
        {
            new->right = (t_node *)ft_calloc(1, sizeof(t_node));
            if (!new->right)
            {
                perror("Failed to allocate memory");
                exit(1);
            }
            new = new->right;
            ast = ast->right;
        }
        else
            break;
        printf("Operation 2: %s, Type: %d\n", new->operation->read, new->operation->type);
    }

    // Print the expanded tree
    print_tree(head);

    return head;
}
