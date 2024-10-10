/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:48:27 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:48:27 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_list_shellenv *shellenv)
{
	t_list_env	*current_env;

	current_env = shellenv->env;
	while (current_env)
	{
		if (current_env->content != NULL)
			printf("%s\n", current_env->content);
		current_env = current_env->next;
	}
	return (0);
}
