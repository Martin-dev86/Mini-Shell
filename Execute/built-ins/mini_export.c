/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:43 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:46:43 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sorted(t_list_env *env)
{
	int	i;
	int	k;

	i = 0;
	while (env && env->next)
	{
		printf("declare -x ");
		i = mini_strlen(env->content);
		k = 0;
		while (i >= 0)
		{
			printf("%c", env->content[k]);
			i--;
			k++;
		}
		printf("\"");
		while (env->content[k])
			printf("%c", env->content[k++]);
		printf("\"\n");
		env = env->next;
	}
}

void	swap_list(t_list_env *env, t_list_env *sorted_env)
{
	int			swapped;
	char		*temp;
	size_t		j;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		env = sorted_env;
		while (env && env->next)
		{
			j = mini_strlen(env->content);
			if (ft_strncmp(env->content, env->next->content, j) > 0)
			{
				temp = env->content;
				env->content = env->next->content;
				env->next->content = temp;
				swapped = 1;
			}
			env = env->next;
		}
	}
}

void	final_unset(t_list_shellenv *shellenv, \
		size_t len, char *final_unset_var)
{
	t_list_env	*current;
	t_list_env	*prev = NULL;
	t_list_env	*last_match = NULL;
	t_list_env	*prev_last_match = NULL;

	current = shellenv->env;
	last_match = NULL;
	while (current)
	{
		if (ft_strncmp(current->content, final_unset_var, len) == 0)
		{
			last_match = current;
			prev_last_match = prev;
		}
		prev = current;
		current = current->next;
	}
	if (last_match != NULL)
	{
		if (prev_last_match != NULL)
			prev_last_match->next = last_match->next;
		else
			shellenv->env = last_match->next;
	}
	free(final_unset_var);
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

int	mini_export(t_list_shellenv *shellenv, t_node *node)
{
	t_list_env	*new_node;
	t_list_env	*promp;
	t_list_env	*sorted_current;
	t_list_env	*env;

	new_node = ft_calloc(1, sizeof(t_list_env));
	if (node->right == NULL)
	{
		sorted_current = NULL;
		env = shellenv->env;
		while (env)
		{
			new_node = mini_lstnew(ft_strdup(env->content));
			mini_lstadd_back(&sorted_current, new_node);
			env = env->next;
		}
		swap_list(shellenv->env, sorted_current);
		env = sorted_current;
		print_sorted(env);
		return (0);
	}
	found_equal(shellenv, node);
	promp = mini_lstnew(ft_strdup(node->right->operation->read));
	mini_lstadd_back(&(shellenv->env), promp);
	update_path(shellenv);
	return (ft_free_env(new_node), 0);
}
