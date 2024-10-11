/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:20:25 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 12:32:49 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_matrix(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// Recursive function to free the AST
void	ft_free_node(t_node *node)
{
	if (node == NULL)
		return ;
	ft_free_node(node->left);
	ft_free_node(node->right);
	if (node->operation != NULL)
		free(node->operation);
	free(node);
}

// Free the environment list
void	ft_free_env_list(t_list_shellenv *shellenv)
{
	t_list_env	*tmp;

	while (shellenv->env)
	{
		tmp = shellenv->env->next;
		if (shellenv->env->content != NULL)
			free(shellenv->env->content);
		if (shellenv->env->path != NULL)
			ft_free_matrix(shellenv->env->path);
		if (shellenv->env->env != NULL)
			ft_free_matrix(shellenv->env->env);
		free(shellenv->env);
		shellenv->env = tmp;
	}
}

// Free the token list
void	ft_free_token_list(t_list_token *token)
{
	t_list_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->content != NULL)
		{
			if (token->content->read != NULL)
				free(token->content->read);
			if (token->content->path != NULL)
				free(token->content->path);
			free(token->content);
		}
		free(token);
		token = tmp;
	}
}

// Free the son structure
void	ft_free_son(t_son *son)
{
	if (son == NULL)
		return ;
	free(son);
}

// Main function to free all structures
void	ft_free(t_list_shellenv *shellenv, t_node *node, t_list_token *token,
		t_son *son)
{
	if (shellenv != NULL && shellenv->env != NULL)
		ft_free_env_list(shellenv);
	if (node != NULL)
		ft_free_node(node);
	if (token != NULL)
		ft_free_token_list(token);
	if (son != NULL)
		ft_free_son(son);
}
