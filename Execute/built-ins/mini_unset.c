/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:47:21 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:47:21 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **mini_unset(char **env, t_token *token)
{
    int i;
    char    *unset_var;
    char    **result;
    
    unset_var = get_env(token->argument[1]);
    while(env[i])
    {
        if (ft_strcmp(token->argument[1], unset_var) == 0)
            i++;
        i++;
    }
}