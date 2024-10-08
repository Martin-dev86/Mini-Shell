/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/09 00:14:06 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt_active;

void	shell_loop(t_list_shellenv *result, t_son *son)
{
	t_token	*token;
	t_node	*node;

	node = ft_calloc(0, sizeof(t_node));
	while (1)
	{
		//prompt_active = 0;
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
		//prompt_active = 1;
		execute(son, result, node);
		free(token->read);
        free(token);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_son				*son;
	t_list_shellenv		*result;

	(void)argc;
	(void)argv;
	ft_baby_yoda_banner();
	setup_signals();
	rl_catch_signals = 0;
	result = (t_list_shellenv *)malloc(sizeof(t_list_shellenv));
	son = malloc(sizeof(t_son));
	if (son == NULL)
		ft_exit("Failed to allocate memory for son", EXIT_FAILURE);
	if (son == NULL)
		ft_exit("Failed to crate node", EXIT_FAILURE);
	result->env = env_parse(env);
	shell_loop(result, son);
	//ft_free(result, node, NULL, son);
	return (son->code);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_token				*token;
// 	t_son				*son;
// 	t_node				*node;
// 	t_list_shellenv		*result;

// 	(void)argc;
// 	(void)argv;
// 	ft_baby_yoda_banner();
// 	setup_signals();
// 	rl_catch_signals = 0;
// 	result = (t_list_shellenv *)malloc(sizeof(t_list_shellenv));
// 	son = malloc(sizeof(t_son));
// 	if (son == NULL)
// 		ft_exit("Failed to allocate memory for son", EXIT_FAILURE);
// 	node = ft_calloc(0, sizeof(t_node));
// 	if (son == NULL)
// 		ft_exit("Failed to crate node", EXIT_FAILURE);
// 	result->env = env_parse(env);
// 	while (1)
// 	{
// 		prompt_active = 0;
// 		token = ft_calloc(1, sizeof(t_token));
// 		if (!token)
// 			ft_exit("Failed to allocate memory for token", EXIT_FAILURE);
// 		token->read = readline("Minishell>");
// 		add_history(token->read);
// 		if (token->read == NULL)
// 			break ;
// 		if (token->read[0] == '\0')
// 			continue ;
// 		if (token->read == NULL)
// 			break ;
// 		node = main_parser(result, token, son);
// 		if (node == NULL)
// 			continue ;
// 		prompt_active = 1;
// 		execute(son, result, node);
// 	}
// 	//ft_free(result, node, NULL, son);
// 	return (son->code);
// }

