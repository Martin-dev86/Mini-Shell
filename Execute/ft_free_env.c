/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:25:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 09:54:25 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_list_env *env)
{
	t_list_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->content != NULL)
			free(env->content);
		free(env);
		env = tmp;
	}
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->left)
		free_node(node->left);
	if (node->right)
		free_node(node->right);
	if (node->operation)
		free(node->operation);
	free(node);
}
