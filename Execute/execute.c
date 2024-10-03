/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/03 17:59:04 by jeandrad         ###   ########.fr       */
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
	waitpid(son->pid, &son->code, 0);
	if (WIFEXITED(son->code))
		son->code = WEXITSTATUS(son->code);
	else if (WIFSIGNALED(son->code))
		son->code = 128 + WTERMSIG(son->code);
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
		mini_env(env);
	if (ft_strcmp(node->operation->read, "exit") == 0)
		mini_exit(node, env, son, 0);
	return (0);
}

int	execute(t_son *son, t_list_env *env, t_node *node)
{
	if (ft_strncmp(node->operation->read, "exit", 4) == 0)
	{
		printf("entra en exit\n");
		mini_exit(node, env, son, 0);
	}
	else if (node->operation->type == REDIR_R
		|| node->operation->type == REDIR_L
		|| node->operation->type == APPEND)
		mini_redirect(node, son, env);
	else if (node->operation->type == BUILTIN)
		execute_builtins(son, env, node);
	else if (node->n_childs <= 1 && node->operation->type == CMD)
		executing(son, env, node);
	else if (node->n_childs >= 2 && node->operation->type == PIPE)
		mini_pipe(son, node, env);
	return (0);
}
