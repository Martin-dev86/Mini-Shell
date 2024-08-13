/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/13 13:49:44 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_execute	*execute;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("Minishell>");
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			break ;
		printf("\n\ninput = %s\n\n", input);
		execute(execute, input);
		add_history(input);
	}
	return (0);
}
