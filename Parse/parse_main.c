/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:45:22 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 11:07:22 by jeandrad         ###   ########.fr       */
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
    
    // Check for an empty token list / command
    if (token_list == NULL)
        exit (EXIT_SUCCESS);
    
    final_state = dfa_main(token_list);
    
    // Check if the token list is syntactically correct
    if (final_state <= 0 || final_state == 2 || final_state == 4)
        ft_exit ("Syntax FAILURE",EXIT_FAILURE);

    // Create the AST
    if (ast = ast_creator(token_list)  == NULL)
        ft_exit("AST FAILURE",EXIT_FAILURE);
    
    // Parse the AST and expand the variables
    if (ast = expand_tree(ast, env_list)  == NULL)
        ft_exit("EXPAND FAILURE",EXIT_FAILURE);
        
    return (EXIT_SUCCESS);
}