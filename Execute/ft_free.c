/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:20:25 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/04 19:36:08 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recursive function to free the AST
void t_free_node(t_node *node)
{
    if (node == NULL)
        return;
    t_free_node(node->left);
    t_free_node(node->right);
    free(node);
}

void ft_free_env_list(t_list_shellenv *shellenv)
{
    t_list_env *tmp;

    while (shellenv->env)
    {
        tmp = shellenv->env->next;
        free(shellenv->env->content);
        free(shellenv->env->path);
        free(shellenv->env->env);
        shellenv->env = tmp;
    }
}

void ft_free_token_list(t_list_token *token)
{
    t_list_token *tmp; // Correct type for tmp

    while (token)
    {
        tmp = token->next;
        free(token->content->read);
        free(token->content->path);
        free(token->content);
        free(token);
        token = tmp;
    }
}

void ft_free_son(t_son *son)
{
    free(son);
}

void ft_free(t_list_shellenv *shellenv, t_node *node, t_list_token *token, t_son *son)
{
    if (shellenv->env != NULL)
        ft_free_env_list(shellenv);
    if (node != NULL)
        t_free_node(node);
    if (token != NULL)
        ft_free_token_list(token);
    if (son != NULL)
        ft_free_son(son);
}