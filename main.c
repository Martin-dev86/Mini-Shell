/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/16 14:09:06 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*content;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		content = readline("Minishell>");
		if (content == NULL || ft_strcmp(content, "exit") == 0)
			break ;
		if (ft_strcmp(content, "pwd") == 0)
			printf("%s\n", ft_get_pwd());
		add_history(content);
	}
	return (0);
}

