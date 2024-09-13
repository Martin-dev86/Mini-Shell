/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:35:19 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/03 22:35:19 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_found(char **array_path, t_node *node)
{
	int		i;
	char	*command;
	char	*cmd;

	i = 0;
	cmd = node->operation->read;
	while (array_path[i])
	{
		command = ft_strjoin(ft_strjoin(array_path[i], "/"), cmd);
		if (access(command, X_OK) == 0)
			break ;
		free(command);
		i++;
	}
	return (command);
}

char	**exe_args(t_node *node)
{
	char	**array_cmd;
	int		i;

	i = 0;
	array_cmd = ft_calloc(0, sizeof(char *));
	while (node)
	{
		array_cmd[i] = node->operation->read;
		printf("Node content == %s \n", array_cmd[i]);
		node = node->right;
		i++;
	}
	return (array_cmd);
}

int	mini_cmd(t_list_env *env, t_son *son, t_node *node)
{
	int		i;
	char	*path_cmd;
	char	**array_cmd;

	i = 0;
	son->pid = fork();
	if (son->pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (son->pid == 0)
	{
		array_cmd = ft_calloc(0, sizeof(char *));
		path_cmd = cmd_found(env->path, node);
		if (node->right == NULL)
		{
			array_cmd = exe_args(node);
			execve(path_cmd, array_cmd, env->env);
			free(array_cmd);
		}
		else
		{
			array_cmd = exe_args(node);
			while (array_cmd[i])
				printf("Node content out == %s \n", array_cmd[i++]);
			execve(path_cmd, array_cmd, env->env);
			free(array_cmd);
		}
		exit (0);
	}
	if (waitpid(son->pid, &son->code, 0) < 0)
	{
		perror("waitpid");
		return (son->code);
	}
	return (son->code);
}
