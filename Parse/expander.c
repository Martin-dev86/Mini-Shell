/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 10:29:28 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will expand the tree
// !!!!!!!!!!!!!!!!!
// This might not work properly yet
t_node *expand_tree(t_node *ast, t_list_env *env)
{
    t_node *new;
    int i;
    
    i = 0;
    new = (t_node *)malloc(sizeof(t_node));
    if (!new)
        exit(1);
    if (ast->operation->type == CMD)
    {
        if ( ft_strchr(ast->operation->read, '$') != NULL )
        {
            while (env)
            {
                ft_strtrim(ast->operation->read, "$");
                if (ft_strncmp(ast->operation->read, env->content, ft_strlen(env->content)) == 0)
                {
                    new->operation->type = CMD;
                    new->operation->read = ft_strdup(env->content);
                    new->left = NULL;
                    new->right = NULL;
                    return (new);
                }
                env = env->next;
            }
        }
    }
    else if (ast->operation->type == REDIR || ast->operation->type == APPEND || ast->operation->type == HEREDOC)
    {
        new->operation->type = ast->operation->type;
        new->operation->read = ft_strdup(ast->operation->read);
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
    new = expand_tree(&ast);
    return (head);
}
