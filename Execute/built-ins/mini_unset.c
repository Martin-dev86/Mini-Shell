/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
	free (node_delete);
}

int	mini_unset(t_list_env *env, t_token *token)
{
	char		*unset_var;
	t_list_env	*current;

	current = env;
	unset_var = ft_strjoin(token->argument[1], "=");
	unset_var = ft_strjoin(unset_var, getenv (token->argument[1]));
	while (current && current->next)
	{
		if (ft_strcmp (current->next->content, unset_var) == 0)
		{
			del_node(current);
			continue ;
		}
		current = current->next;
	}
	free(unset_var);
	return (0);
}
