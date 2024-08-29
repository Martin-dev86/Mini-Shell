/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:57:35 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/29 13:01:45 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prototype to create all the nodes in a while
// Then all the nodes are parsed to create the definitive AST
t_node *node_creator(t_list_token *token_list)
{
    t_node *node;

    node = ft_calloc(1, sizeof(t_node));
    node->operation = token_list->content;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

//Main AST creator taht returns the root node
t_node    *ast_creator(t_list_token *token_list)
{
    t_node	*ast;
    int i;

    i = 0;
    ast = ft_calloc(1, sizeof(t_node));
    //while ()

    return (ast);
}