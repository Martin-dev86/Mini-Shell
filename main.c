/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:06 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/15 18:49:53 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void);

int	main(int argc, char **argv, char **env)
{
	//t_token		*token;

	(void)argc;
	(void)argv;
	(void)env;

	char	*content;
	while (1)
	{
		content = readline("Minishell>");
		if (content == NULL || ft_strcmp(content, "exit") == 0)
			break ;
		//printf("%s", holiiiii());
		if (ft_strcmp(content, "pwd") == 0)
			printf("%s\n", ft_get_pwd());
		// parse(token, env);
		// execute(execute, token->content);
		add_history(content);
	}
	return (0);
}

