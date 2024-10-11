/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:55:55 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 10:04:14 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(t_token *token)
{
	if (token)
	{
		if (token->read != NULL)
		{
			free(token->read);
			token->read = NULL;
		}
		if (token->path != NULL)
		{
			free(token->path);
			token->path = NULL;
		}
		free(token);
		token = NULL;
	}
}
