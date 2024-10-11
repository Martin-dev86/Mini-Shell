/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/11 13:04:25 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executing(t_son *son, t_list_shellenv *shellenv, t_node *node)
{
	int	last_status;

	son->pid = fork();
	g_prompt_active = son->pid;
	if (son->pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (son->pid == 0)
	{
		son->code = mini_cmd(shellenv, son, node);
		exit (son->code);
	}
	waitpid(son->pid, &son->code, 0);
	if (WIFEXITED(son->code))
		last_status = WEXITSTATUS(son->code);
	else if (WIFSIGNALED(son->code))
		last_status = 128 + WTERMSIG(son->code);
	son->code = last_status;
	return (last_status);
}

int	execute_builtins(t_son *son, t_list_shellenv *shellenv, t_node *node)
{
	if (node->left)
	{
		node = node->left;
		execute(son, shellenv, node);
	}
	if (ft_strcmp(node->operation->read, "pwd") == 0)
		mini_pwd(son);
	if (ft_strcmp(node->operation->read, "echo") == 0)
		mini_echo(node, son);
	if (ft_strcmp(node->operation->read, "unset") == 0)
		mini_unset(shellenv, node);
	if (ft_strcmp(node->operation->read, "cd") == 0)
		mini_cd(node, shellenv);
	if (ft_strcmp(node->operation->read, "export") == 0)
		mini_export(shellenv, node);
	if (ft_strcmp(node->operation->read, "env") == 0)
		mini_env(shellenv);
	if (ft_strcmp(node->operation->read, "exit") == 0)
		mini_exit(node, shellenv, son, 0);
	return (0);
}

int	execute(t_son *son, t_list_shellenv *shellenv, t_node *node)
{
	if (ft_strncmp(node->operation->read, "exit", 4) == 0)
		mini_exit(node, shellenv, son, 0);
	else if (node->operation->type == HEREDOC)
		handle_heredoc(node, son);
	else if (node->operation->type == REDIR_R
		|| node->operation->type == REDIR_L
		|| node->operation->type == APPEND)
		son->code = mini_redirect(node, son, shellenv);
	else if (node->operation->type == BUILTIN)
		son->code = execute_builtins(son, shellenv, node);
	else if (node->n_childs <= 1 && node->operation->type == CMD)
		son->code = executing(son, shellenv, node);
	else if (node->n_childs >= 2 && node->operation->type == PIPE)
		son->code = mini_pipe(son, node, shellenv);
	return (0);
}
