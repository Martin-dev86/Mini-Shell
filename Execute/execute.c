/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/23 00:06:26 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_token *token, t_son *son, char **env)
{
	if (ft_strcmp(token->argument[0], "pwd") == 0)
		mini_pwd(son, token);
	if (ft_strcmp(token->argument[0], "echo") == 0)
		mini_echo(son, token);
	if (ft_strcmp((token->argument[0], "unset") == 0))
		mini_unset(env);
	if (ft_strcmp(token->argument[0], "env") == 0)
			if	(mini_env(env) != 0)
				{
					perror("Path");
					exit(EXIT_FAILURE);
				}
	return (0);
}

int	execute(t_token *token, t_son *son, char **env)
{
	if (token->type == REDIR)
		mini_redirect(token, son);
	if (token->type == BUILTIN)
		execute_builtins(token, son);	
	return (0);
}
