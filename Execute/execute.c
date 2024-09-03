/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/03 01:01:25 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_token *token, t_son *son, t_list_env *env)
{
	(void)*env;
	if (ft_strcmp(token->argument[0], "pwd") == 0)
		mini_pwd(son, token);
	if (ft_strcmp(token->argument[0], "echo") == 0)
		mini_echo(son, token);
	if (ft_strcmp(token->argument[0], "unset") == 0)
		mini_unset(env, token);
	if (ft_strcmp(token->argument[0], "cd") == 0)
		mini_cd(token);
	if (ft_strcmp(token->argument[0], "export") == 0)
		mini_export(env, token);
	if (ft_strcmp(token->argument[0], "env") == 0)
	{
		if (mini_env(env) != 0)
		{
			perror("Path");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	execute(t_token *token, t_son *son, t_list_env *env)
{
	if (token->type == REDIR)
		mini_redirect(token, son);
	if (token->type == BUILTIN)
		execute_builtins(token, son, env);
	return (0);
}
