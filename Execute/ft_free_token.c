/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:55:55 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/02 19:06:03 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(t_token *token)
{
    if (token)
    {
        // Debug prints
        printf("Freeing token: %p\n", (void *)token);
        printf("Token read: %p\n", (void *)token->read);
        printf("Token path: %p\n", (void *)token->path);

        if (token->read)
        {
            free(token->read);
            token->read = NULL;
        }
        if (token->path)
        {
            free(token->path);
            token->path = NULL;
        }
        free(token);
        token = NULL;

        // Debug prints
        printf("Token freed successfully\n");
    }
    else
    {
        // Debug prints
        printf("Token is NULL, nothing to free\n");
    }
}