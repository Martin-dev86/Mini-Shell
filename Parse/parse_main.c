/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:45:22 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/11 18:58:16 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void print_tokens(t_list_token *head)
{
    t_list_token *current = head;
    while (current != NULL)
    {
        printf("Token: %s, Type: %d, Priority: %d, Previous: %s, Next: %s\n",
               current->content->read,
               current->content->type,
               current->content->priority,
               current->prev ? current->prev->content->read : "NULL",
               current->next ? current->next->content->read : "NULL");
        current = current->next;
    }
}

t_node *main_parser(char **env, t_token *token)
{
    t_list_env *env_list;
    t_list_token *token_list;
    t_node *ast;
    int final_state;

    final_state = 0;

    // Check the environment variables
    // Should only be done once so maybe I have to take it out of here
    env_list = ft_calloc(1, sizeof(t_list_env));
    env_list = env_parse(env);
    
    token_list = ft_calloc(1, sizeof(t_list_token));
    token_list = token_read_filler(*token, token_list);
    token_list_typer(token_list);
    
    // Check for an empty token list / command
    if (token_list == NULL)
        exit (EXIT_SUCCESS);
    
    // The DFA is not doing his job correctly
    final_state = dfa_main(token_list);
    
    // Delete the line below, it's just to check the final state
    printf("Final state: %d\n", final_state);

    // Check if the token list is syntactically correct
    if (final_state <= 0 || final_state == 2 || final_state == 4)
        ft_exit("Syntax FAILURE", EXIT_FAILURE);
        
    // Print the token list to check if it was created correctly
    //printf("Printing token list:\n");
    //print_tokens(token_list);

    // Create the AST
    printf("Creating AST\n");
    // Find the last token in the list
    t_list_token *end = token_list;
    while (end->next != NULL)
        end = end->next;
    //printf("Start token: %s\n", token_list->content->read);
    //printf("End token: %s\n", end->content->read);
    // Create the AST
    ast = ast_creator(token_list, end);
    printf("Created AST\n");

    if (ast == NULL)
        ft_exit("AST FAILURE", EXIT_FAILURE);
    // Print the AST to check if it was created correctly
    print_ast(ast);
    
    // Parse the AST and expand the variables
    printf("list: %s\n", env_list->content);
    // printf("Expanding AST\n");
    // ast = final_tree(ast, env_list);
    // printf("Expander finished!\n");
    // if (ast == NULL)
    //     ft_exit("EXPAND FAILURE", EXIT_FAILURE);
        
    return (ast);
}