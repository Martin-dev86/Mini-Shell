/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/02 20:22:34 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	t_token		*token;
	t_son		*son;
	t_node		*node;
	t_list_env	*result;
	struct		sigaction sa;

	(void)argc;
	(void)argv;
	result = (t_list_env *)malloc(sizeof(t_list_env));
	son = malloc(sizeof(t_son));
	if (son == NULL)
		ft_exit("Failed to allocate memory for son", EXIT_FAILURE);
	node = ft_calloc(0, sizeof(t_node));
	if (son == NULL)
		ft_exit("Failed to crate node", EXIT_FAILURE);
	result = env_parse(env);
	sa.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		token = ft_calloc(1, sizeof(t_token));
		if (!token)
			ft_exit("Failed to allocate memory for token", EXIT_FAILURE);
		token->read = readline("Minishell>");
		if (token->read == NULL)
			break ;
		if (token->read[0] == '\0')
			continue ;
		if (token->read == NULL || ft_strcmp(token->read, "exit") == 0)
			break ;
		node = main_parser(env, token);
		execute(son, result, node);
		add_history(token->read);
	}
	ft_free(result, node, NULL, son);
	return (0);
}
