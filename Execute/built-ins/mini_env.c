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

int	mini_env(t_list_env *env)
{
<<<<<<< HEAD
	t_list	*current_env;
=======
	t_list_env	*current_env;
>>>>>>> origin/Master

	current_env = env;
	while (current_env)
	{
<<<<<<< HEAD
		printf("%s\n", env->content);
		current_env = env->next;
=======
		printf("%s\n", current_env->content);
		current_env = current_env->next;
>>>>>>> origin/Master
	}
	return (0);
}
