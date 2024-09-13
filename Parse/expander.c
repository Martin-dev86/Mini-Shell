/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/13 19:35:20 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_node *final_tree(t_node *ast, t_list_env *env)
{
    if (ast == NULL)
        return NULL;

    (void ) env;
    t_node *new = (t_node *)ft_calloc(1, sizeof(t_node));
    if (!new)
        ft_exit("Failed to allocate memory", EXIT_FAILURE);    
    t_node *head = new;

    // Traverse the tree and change types to BUILTIN where applicable
    while (ast != NULL)
    {
        printf("Operation: new\n");
        new->operation = ast->operation;
        printf("ABCº\n");
        //new = expand_string(ast, env); // This will change the type to BUILTIN if applicable

        printf("Operation: %s, Type: %d\n", new->operation->read, new->operation->type);
        if (ast->left != NULL)
        {
            printf("Enters in right\n");
            new->left = (t_node *)ft_calloc(1, sizeof(t_node));
            printf("A\n");
            if (!new->left)
                ft_exit("Failed to allocate memory", EXIT_FAILURE);
            printf("B\n");
            new = new->left;
            printf("C\n");
            ast = ast->left;
            printf("D\n");
        }
        else if (ast->right != NULL)
        {   
            printf("Enters in left\n");
            printf("Operation 1: %s, Type: %d\n", new->operation->read, new->operation->type);
            new->right = (t_node *)ft_calloc(1, sizeof(t_node)); // Allocate at least 1 byte
            printf("A2\n");
            if (!new->right)
                ft_exit("Failed to allocate memory", EXIT_FAILURE);
            printf("B2\n");
            new = new->right;
            printf("C2\n");
            ast = ast->right;
            printf("D2\n");
        }
        else
        {
            printf("Enters in else to break\n");
            break;
        }
        printf("Operation 2: %s, Type: %d\n", new->operation->read, new->operation->type);
    }
    return head;
}