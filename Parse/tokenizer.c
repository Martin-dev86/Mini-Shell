/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:59:22 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/19 19:48:22 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void token_typer (t_token *token)
{
    
}

void    env_parse(char *str, char **env)
{
    char *result;

    if (env == NULL)
    {
        
    };
    result = NULL;
    str = strtrim(str, "$");
    result = getenv(str);
    if (!result)
        return ("");
}

char **token_maker(t_token *token, char **env)
{
    char **str;
    int i;

    i = 0;
    str = ft_split(token->content, ' ');
    //This goes inside the more detailed parser AFTER the tokens are made, maybe ¿?.
    while (str[i])
    {
        if (strchr(str[i][0], '$'))
        {
            env_parse(str[i], env);
        }
        token->content = str[i];
        i++;
    }
    token_typer(token);
    return (str);
}
