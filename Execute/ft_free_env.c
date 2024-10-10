/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:25:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 16:26:21 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_list_env *env)
{
	t_list_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->content != NULL)
			free(env->content);
		free(env);
		env = tmp;
	}
}
