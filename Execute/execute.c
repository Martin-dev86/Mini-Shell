/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/18 19:51:43 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executing(t_son *son, t_list_env *env, t_node *node)
{
	son->pid = fork();
	if (son->pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (son->pid == 0)
	{
		mini_cmd(env, son, node);
		exit (son->code);
	}
	if (waitpid(son->pid, &son->code, 0) < 0)
	{
		perror("waitpid");
		return (son->code);
	}
	return (son->code);
}

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
		mini_echo(node);
	if (ft_strcmp(node->operation->read, "unset") == 0)
		mini_unset(env, node);
	if (ft_strcmp(node->operation->read, "cd") == 0)
		mini_cd(node, env);
	if (ft_strcmp(node->operation->read, "export") == 0)
		mini_export(env, node);
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
		mini_redirect(node, son, env);
	else if (node->operation->type == BUILTIN)
		execute_builtins(son, env, node);
	else if (node->n_childs <= 1 && node->operation->type == CMD)
		executing(son, env, node);
	else if (node->n_childs >= 2 && node->operation->type == PIPE)
		mini_pipe(son, node, env);
	return (0);
}
