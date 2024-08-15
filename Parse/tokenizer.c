/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:59:22 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/15 16:51:34 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

// # include <fcntl.h>
// # include <memory.h>
// # include <stdint.h>
// # include <stddef.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <limits.h>
// # include "libft.h"
// # include <readline/readline.h>
// # include <readline/history.h>
// # include "../includes/parse.h"

// void    env_parse(char *str, char **env)
// {
//     char *result;
    
//     result = NULL;
//     str = ft_strtrim(str, "$");
//     result = getenv(str);
//     if (!result)
//         result = "";
// }

// char **token_maker(t_token *token, char **env)
// {
//     char **str;
//     int i;

//     i = 0;
//     str = ft_split(token->content, ' ');
//     while (str[i])
//     {
//         if (strchr(str[i][0], '$'))
//             env_parse(str[i], env);
//         token->content = str[i];
//         i++;
//     }
//     return (str);
// }

/*
 int main(int argc, char *argv, char *env)
 {
        t_token *token;
        char **str;

        (void)argc;
        (void)argv;
        while (1)
        {
            token->content = readline("Minishell>");
            if (token->content == NULL || strcmp(token->content, "exit") == 0)
                break ;
            str = token_maker(token, env);
            int i = 0;
            while (str[i])
            {
                printf("\n\ntoken->content = %s\n\n", str[i]);
                i++;
            }
            add_history(token->content);
        }
        return (0);
 }
 */