/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/11 12:50:02 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_prompt_active;

void	shell_loop(t_list_shellenv *result, t_son *son)
{
	t_token	*token;
	t_node	*node;

	while (1)
	{
		result->env->env = create_env_matrix(result->env);
		token = ft_calloc(1, sizeof(t_token));
		if (!token)
			ft_exit("Failed to allocate memory for token", EXIT_FAILURE);
		token->read = readline("Minishell>");
		if (token->read == NULL)
			break ;
		if (token->read[0] == '\0')
			continue ;
		add_history(token->read);
		node = main_parser(result, token, son);
		if (node == NULL)
			continue ;
		update_path(result);
		execute(son, result, node);
		ft_free_node(node);
		free(token);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_son			*son;
	t_list_shellenv	*result;

	(void)argc;
	(void)argv;
	first_env(env);
	setup_signals();
	rl_catch_signals = 0;
	result = (t_list_shellenv *)malloc(sizeof(t_list_shellenv));
	son = ft_calloc(1, sizeof(t_son));
	if (son == NULL)
		ft_exit("Failed to allocate memory for son", EXIT_FAILURE);
	if (son == NULL)
		ft_exit("Failed to crate node", EXIT_FAILURE);
	result->env = env_parse(env);
	shell_loop(result, son);
	ft_free(result, NULL, NULL, son);
	return (son->code);
}
