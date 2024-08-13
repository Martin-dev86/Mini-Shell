/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/13 18:15:50 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_token		*token;

	(void)argc;
	(void)argv;
	while (1)
	{
		token->content = readline("Minishell>");
		if (token->content == NULL || ft_strcmp(token->content, "exit") == 0)
			break ;
		printf("\n\ntoken->content = %s\n\n", token->content);
		token_maker(token, env);
		//execute(execute, token->content);
		add_history(token->content);
	}
	return (0);
}
