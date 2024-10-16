/* ************************************************************************** */
/*																		    */
/*												        :::      ::::::::   */
/*   mini_cd.c									      :+:      :+:    :+:   */
/*												    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*												+#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:08 by cagarci2          #+#    #+#			 */
/*   Updated: 2024/08/22 23:46:08 by cagarci2         ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#include "minishell.h"

char	*get_temp_directory(t_list_shellenv *shellenv)
{
	t_list_env	*current;
	char		*temp;
	int			i;

	i = 0;
	current = shellenv->env;
	while (current && current->next)
	{
		shellenv->env->variable_len = mini_strlen(current->content);
		if (ft_strncmp(current->content, "USER=", \
			shellenv->env->variable_len) == 0)
		{
			temp = malloc(sizeof(char) * (mini_strlen(current->content) + 8));
			if (!temp)
				return (NULL);
			while (current->content[shellenv->env->len])
				temp[i++] = current->content[shellenv->env->len++];
			temp[i] = '\0';
			return (ft_strjoin("/home/", temp));
		}
		current = current->next;
	}
	return (NULL);
}

int	mini_cd(t_node *node, t_list_shellenv *shellenv)
{
	char		*home;

	(void) shellenv->env;
	if (node->right == NULL)
	{
		home = getenv("HOME");
		if (chdir(home) == -1)
			ft_exit("change directory fail\n", 1);
		return (0);
	}
	else
	{
		if (chdir(node->right->operation->read) == -1)
			printf("change directory fail\n");
		return (1);
	}
	return (0);
}
