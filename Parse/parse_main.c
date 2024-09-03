/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:45:22 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/03 16:02:55 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main_parser(int argc, char **argv, char **env, t_token *token)
{
    t_list_env *env_list;
    t_list_token *token_list;
    t_node *ast;
    int final_state;

    final_state = 0;
    ft_calloc(1, sizeof(t_list_env));
    env_list = env_parse(env);
    token_list = token_read_filler(token, token_list);
    dfa_main(token_list);
    
    //check if the token list is syntactically correct
    if (final_state <= 0 || final_state == 2 || final_state == 4)
    {
        ft_putstr_fd("Syntax error\n", 2);
        exit (1);
    }

    // create the AST
    ast = ast_creator(token_list);
    
    // parse the AST and expand the variables

    return (0);
}