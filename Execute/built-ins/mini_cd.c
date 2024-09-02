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

int	mini_cd(t_token *token)
{
	if (!token->argument[1])
		return (1);
	if (chdir(token->argument[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
