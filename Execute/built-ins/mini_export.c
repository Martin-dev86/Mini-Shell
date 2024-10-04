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

int	mini_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '=')
		i++;
	i++;
	return (i);
}

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

int	mini_export(t_list_shellenv *shellenv, t_node *node)
{
	t_list_env	*new_node;
	t_list_env	*promp;
	t_list_env	*sorted_current;
	t_list_env	*env;

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
	promp = mini_lstnew(node->right->operation->read);
	mini_lstadd_back(&(shellenv->env), promp);
	return (0);
}
