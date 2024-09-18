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

void	print_sorted(t_list_env *current)
{
	int	i;
	int	k;

	i = 0;
	while (current && current->next)
	{
		printf("declare -x ");
		i = mini_strlen(current->content);
		k = 0;
		while (i >= 0)
		{
			printf("%c", current->content[k]);
			i--;
			k++;
		}
		printf("\"");
		while (current->content[k])
			printf("%c", current->content[k++]);
		printf("\"\n");
		current = current->next;
	}
}

void	swap_list(t_list_env *current, t_list_env *sorted_current)
{
	int			swapped;
	char		*temp;
	size_t		j;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = sorted_current;
		while (current && current->next)
		{
			j = mini_strlen(current->content);
			if (ft_strncmp(current->content, current->next->content, j) > 0)
			{
				temp = current->content;
				current->content = current->next->content;
				current->next->content = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

int	mini_export(t_list_env *env, t_node *node)
{
	t_list_env	*new_node;
	t_list_env	*promp;
	t_list_env	*current;
	t_list_env	*sorted_current;

	if (node->right == NULL)
	{
		sorted_current = NULL;
		current = env;
		while (current)
		{
			new_node = mini_lstnew(ft_strdup(current->content));
			mini_lstadd_back(&sorted_current, new_node);
			current = current->next;
		}
		swap_list(current, sorted_current);
		current = sorted_current;
		print_sorted(current);
		return (0);
	}
	promp = mini_lstnew(node->right->operation->read);
	mini_lstadd_back(&env, promp);
	return (0);
}
