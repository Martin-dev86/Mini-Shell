/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/22 23:47:21 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:47:21 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_list_env *env)
{
	t_list_env	*node_delete;

	if (env == NULL || env->next == NULL)
		return ;
	node_delete = env->next;
	env->next = node_delete->next;
	if (node_delete->content != NULL)
	{
		free(node_delete->content);
		node_delete->content = NULL;
	}
	free(node_delete);
}

int	mini_unset(t_list_shellenv *shellenv, t_node *node)
{
	char		*unset_var;
	t_list_env	*current;
	size_t		len;

	current = shellenv->env;
	unset_var = ft_strjoin(node->right->operation->read, "=");
	len = ft_strlen(unset_var);
	while (current && current->next != NULL)
	{
		if (ft_strncmp(current->next->content, unset_var, len) == 0)
		{
			del_node(current);
			continue ;
		}
		if (current->next == NULL)
			break;
		current = current->next;
	}
	free(unset_var);
	update_path(shellenv);
	return (0);
}
