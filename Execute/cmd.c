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

char	*cmd_found(char **array_path, char *cmd)
{
	int		i;
	char	*command;

	i = 0;
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

int mini_cmd(t_list_env *env, t_token *token, t_son *son)
{
	int		i;
    char    *path_cmd;

	i = 0;
	son->pid = fork();
	if (son->pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (son->pid == 0)
	{
        path_cmd = cmd_found("array path", token->argument);
        if(exceve(path_cmd, , env))
		exit (0);
	}
	if (waitpid(son->pid, &son->code, 0) < 0)
	{
		perror("waitpid");
		return (son->code);
	}
	return (son->code);
}
