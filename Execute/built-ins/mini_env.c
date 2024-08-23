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

int	mini_env(t_list *env)
{
	char	*current_env;

	current_env = *env;
	while (current_env->next != NULL)
	{
		printf("%s\n", env->content);
		env->next 
	}
	return (0);
}