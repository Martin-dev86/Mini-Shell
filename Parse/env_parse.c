/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:02:15 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/28 10:51:52 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void first_env(char **env)
{   
    if (env== NULL)
        exit (1);
    else if (!getenv("PATH"))
        exit(1);
    else if (!getenv("USER"))
        exit(1);
    else if (!getenv("HOME"))
        exit(1);
    else if (!getenv("PWD"))
        exit(1);
    else if (!getenv("OLDPWD"))
        exit(1);
}

t_list_env env_parse(char **env)
{
    t_list_env *env_list;

    ft_calloc(1, sizeof(t_list_env));
    first_env(env);
    
    // Get the environment variables
    int i;
    t_list_env *new;
    
    new = (t_list_env *)malloc(sizeof(t_list_env));
    if (!new)
        exit(1);
    i = 0;
    while (env[i])
    {
        new->content = env[i];
        new = new->next;
        new->next = NULL;
        i++;
    }
    return (env_list);
}
