/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/10 12:30:47 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_prompt_active;

void	find_and_set_path(t_list_shellenv *env_list)
{
	t_list_env	*current;
	char		*path_value;

	current = env_list->env;
	while (current)
	{
		if (ft_strncmp(current->content, "PATH=", 5) == 0)
		{
			path_value = current->content + 5;
			current->path = get_path(path_value);
			break ;
		}
		current = current->next;
	}
}

void	shell_loop(t_list_shellenv *result, t_son *son)
{
	t_token	*token;
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
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
		//find_and_set_path(result);
		execute(son, result, node);
		//free(result->env);
		//result->env = env_parse(result->env->env);
		//free(token->read);
		//free(token);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_son			*son;
	t_list_shellenv	*result;

	(void)argc;
	(void)argv;
	first_env(env);
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
	ft_free(result, NULL, NULL, son);
	return (son->code);
}
