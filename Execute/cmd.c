/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/03 22:35:19 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/03 22:35:19 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(t_list_shellenv *shellenv)
{
	if (shellenv->env->path)
		ft_free_matrix(shellenv->env->path);
	if (shellenv->env)
		shellenv->env->path = get_path(shellenv->env);
}

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
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

int	count_nodes(t_node *node)
{
	int	count;

	count = 0;
	while (node)
	{
		count++;
		node = node->right;
	}
	return (count);
}

char	**exe_args(t_node *node)
{
	char	**array_cmd;
	int		i;
	int		node_count;

	i = 0;
	node_count = count_nodes(node);
	array_cmd = ft_calloc(node_count + 1, sizeof(char *));
	while (node)
	{
		array_cmd[i] = ft_strdup(node->operation->read);
		node = node->right;
		i++;
	}
	array_cmd[i] = NULL;
	return (array_cmd);
}

int	mini_cmd(t_list_shellenv *shellenv, t_son *son, t_node *node)
{
	char	*path_cmd;
	char	**array_cmd;

	update_path(shellenv);
	if (shellenv->env->path == NULL)
	{
		printf("Command not found: %s\n", node->operation->read);
		return (127);
	}
	path_cmd = cmd_found(shellenv->env->path, node);
	if (!path_cmd)
	{
		printf("Command not found: %s\n", node->operation->read);
		return (127);
	}
	array_cmd = exe_args(node);
	if (execve(path_cmd, array_cmd, shellenv->env->env) == -1)
	{
		perror("execve");
		exit(127);
	}
	return (son->code);
}
