/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:00:29 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/15 19:29:57 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	*holiiiii(void)
// {
// 	return ("hola");
// }

char	*ft_get_pwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * 1024);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, 1024) != NULL)
		return (cwd);
	else
	{
		perror("getcwd");
		free(cwd);
		return (NULL);
	}
}
// int	main(int argc, char **argv, char **env)
// {
// 	//t_token		*token;

// 	(void)argc;
// 	(void)argv;
// 	(void)env;

// 	char	*content;
// 	while (1)
// 	{
// 		content = readline("Minishell>");
// 		if (content == NULL || ft_strcmp(content, "exit") == 0)
// 			break ;
// 		//printf("%s", holiiiii());
// 		if (ft_strcmp(content, "pwd") == 0)
// 			printf("%s\n", ft_get_pwd());
// 		// parse(token, env);
// 		// execute(execute, token->content);
// 		add_history(content);
// 	}
// 	return (0);
// }
