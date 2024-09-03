/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/23 13:24:31 by cagarci2         ###   ########.fr       */
=======
/*   Updated: 2024/09/03 18:06:58 by cagarci2         ###   ########.fr       */
>>>>>>> origin/Master
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int	execute_builtins(t_token *token, t_son *son, t_list *env)
=======
int	execute_builtins(t_token *token, t_son *son, t_list_env *env)
>>>>>>> origin/Master
{
	(void)*env;
	if (ft_strcmp(token->argument[0], "pwd") == 0)
		mini_pwd(son, token);
	if (ft_strcmp(token->argument[0], "echo") == 0)
		mini_echo(son, token);
<<<<<<< HEAD
	if (ft_strcmp((token->argument[0], "unset") == 0))
		mini_unset(env);
=======
	if (ft_strcmp(token->argument[0], "unset") == 0)
		mini_unset(env, token);
	if (ft_strcmp(token->argument[0], "cd") == 0)
		mini_cd(token, env);
	if (ft_strcmp(token->argument[0], "export") == 0)
		mini_export(env, token);
>>>>>>> origin/Master
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

<<<<<<< HEAD
int	execute(t_token *token, t_son *son, t_list *env)
=======
int	execute(t_token *token, t_son *son, t_list_env *env)
>>>>>>> origin/Master
{
	if (token->type == REDIR)
		mini_redirect(token, son);
	if (token->type == BUILTIN)
		execute_builtins(token, son, env);
	return (0);
}
