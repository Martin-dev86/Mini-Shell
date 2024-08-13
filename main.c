/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/13 20:58:27 by cagarci2         ###   ########.fr       */
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
		parse(token, env);
		execute(execute, token->content);
		add_history(token->content);
	}
	return (0);
}

