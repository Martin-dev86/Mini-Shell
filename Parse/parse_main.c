/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:45:22 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 08:04:55 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*main_parser(t_list_shellenv *shellenv, t_token *token, t_son *son)
{
	t_list_token	*token_list;
	t_node			*ast;
	int				final_state;
	t_list_token	*end;

	final_state = 0;
	token->read = replace_variables(token->read, shellenv, son);
	token_list = ft_calloc(1, sizeof(t_list_token));
	token_list = token_read_filler(*token, token_list);
	if (token_list->content == NULL)
		return (NULL);
	token_list_typer(token_list);
	final_state = dfa_main(token_list);
	if (final_state <= 0 || final_state == 2 || final_state == 4)
		return (NULL);
	end = token_list;
	while (end->next != NULL)
		end = end->next;
	ast = ast_creator(token_list, end);
	if (ast == NULL)
		return (NULL);
	ast->n_childs = count_pipe_tokens(ast);
	ast = final_tree(ast, shellenv);
	free_token_list_without_content(token_list);
	//print_ast(ast);
	return (ast);
}
