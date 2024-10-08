/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:55:26 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 19:55:43 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_env(char **env)
{
	if (env == NULL || *env == NULL)
		ft_exit("NO ENV", 128);
	else if (!getenv("PATH"))
		ft_exit("NO PATH", EXIT_FAILURE);
	else if (!getenv("USER"))
		ft_exit("NO USER", EXIT_FAILURE);
	else if (!getenv("HOME"))
		ft_exit("NO HOME", EXIT_FAILURE);
	else if (!getenv("PWD"))
		ft_exit("NO PWD", EXIT_FAILURE);
}
