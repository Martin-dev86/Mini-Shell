/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/13 20:26:53 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_son *son, t_list_env *env, t_node *node)
{
	if (node->left)
	{
		node = node->left;
		execute(son, env, node);
	}
	if (ft_strcmp(node->operation->read, "pwd") == 0)
		mini_pwd(son);
	if (ft_strcmp(node->operation->read, "echo") == 0)
		mini_echo(son, node->operation);
	if (ft_strcmp(node->operation->read, "unset") == 0)
		mini_unset(env, node->operation);
	if (ft_strcmp(node->operation->read, "cd") == 0)
		mini_cd(node->operation, env);
	if (ft_strcmp(node->operation->read, "export") == 0)
		mini_export(env, node->operation);
	if (ft_strcmp(node->operation->read, "env") == 0)
	{
		if (mini_env(env) != 0)
		{
			perror("Path");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	execute(t_son *son, t_list_env *env, t_node *node)
{
	if (node->operation->type == REDIR)
		mini_redirect(node->operation, son);
	if (node->operation->type == BUILTIN)
		execute_builtins(son, env, node);
	if (node->operation->type == CMD)
		mini_cmd(env, son, node);
	if (node->operation->type == PIPE)
		mini_pipe(son, node);
	return (0);
}
