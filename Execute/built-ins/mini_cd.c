/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:08 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:46:08 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(t_node *node, t_list_shellenv *shellenv)
{
	t_list_env	*current;
	char		*temp;
	int			i;

	i = 0;
	shellenv->env->len = 0;
	current = shellenv->env;
	if (node->right == NULL)
	{
		while (current && current->next)
		{
			shellenv->env->variable_len = mini_strlen(current->content);
			shellenv->env->len = shellenv->env->variable_len;
			if (ft_strncmp(current->content, "USER=", shellenv->env->variable_len) == 0)
			{
				while (current->content[shellenv->env->len])
				{
					temp[i] = current->content[shellenv->env->len];
					i++;
					shellenv->env->len++;
				}
				temp = ft_strjoin("/home/", temp);
			}
			current = current->next;
		}
		current = shellenv->env;
		while (current && current->next)
		{
			shellenv->env->variable_len = mini_strlen(current->content);
			shellenv->env->len = shellenv->env->variable_len;
			if (ft_strncmp(current->content, "PWD=", shellenv->env->variable_len) == 0)
				chdir(temp);
			current = current->next;
		}
	}
	current = shellenv->env;
	while (current && current->next)
	{
		shellenv->env->variable_len = mini_strlen(current->content);
		if (ft_strncmp(current->content, "PWD=", shellenv->env->variable_len) == 0)
			temp = current->content;
		if (ft_strncmp(current->content, "OLDPWD=", shellenv->env->variable_len) == 0)
			chdir(temp);
		current = current->next;
	}
	if (!node->right)
		return (1);
	if (chdir(node->right->operation->read) == -1)
	{
		perror("cd");
		return (1);
	}
return (0);
}
