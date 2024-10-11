/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:33:17 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 08:34:39 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*find_last_match(t_list_env *env, size_t len, \
	char *final_unset_var, t_list_env **prev_last_match)
{
	t_list_env	*current;
	t_list_env	*prev;
	t_list_env	*last_match;

	prev = NULL;
	last_match = NULL;
	*prev_last_match = NULL;
	current = env;
	while (current)
	{
		if (ft_strncmp(current->content, final_unset_var, len) == 0)
		{
			last_match = current;
			*prev_last_match = prev;
		}
		prev = current;
		current = current->next;
	}
	return (last_match);
}

void	found_equal(t_list_shellenv *shellenv, t_node *node)
{
	char		*unset_var;
	size_t		len;
	char		*final_unset_var;
	char		*equals_pos;

	equals_pos = ft_strchr(node->right->operation->read, '=');
	if (equals_pos != NULL)
		unset_var = ft_substr(node->right->operation->read, 0, \
		equals_pos - node->right->operation->read);
	else
		unset_var = ft_strdup(node->right->operation->read);
	final_unset_var = ft_strjoin(unset_var, "=");
	free(unset_var);
	len = ft_strlen(final_unset_var);
	final_unset(shellenv, len, final_unset_var);
}
