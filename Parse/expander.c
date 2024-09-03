/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/03 17:06:25 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_node *expand_tree(t_node *ast)
{
    t_node *new;
    
    new = (t_node *)malloc(sizeof(t_node));
    if (!new)
        exit(1);
    if (ast->operation->type == CMD)
    {
        new->type = CMD;
        new->content = ft_strdup(ast->content);
        new->left = NULL;
        new->right = NULL;
    }
    else if (ast->type == REDIR || ast->type == APPEND || ast->type == HEREDOC)
    {
        new->type = ast->type;
        new->content = ft_strdup(ast->content);
        new->left = expand_tree(ast->left);
        new->right = expand_tree(ast->right);
    }
}

// This function will expand the tree
// This returns the final tree to take to the executor
t_node *final_tree (t_node ast)
{
    t_node *new;
    t_node *head;
    
    new = (t_node *)malloc(sizeof(t_node));
    head = new;
    if (!new)
        exit(1);
    new = expand_tree(ast);
    return (head);
}