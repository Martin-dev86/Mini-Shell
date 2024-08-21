/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:17:00 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/21 15:17:00 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_redirect(t_token *token, t_son *son, int flag)
{
	if (flag == WRITE)
	{
		son->fd_out = open(token->argument[token->len - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (son->fd_out < 0)
		{
			perror("output");
			exit (1);
		}
		dup2(son->fd_out, STDOUT_FILENO);
		close(son->fd_out);
	}
	else
	{
		son->fd_in = open(token->argument[1], O_RDONLY);
		if (son->fd_in < 0)
		{
			perror("input");
			exit (1);
		}
		dup2(son->fd_in, STDIN_FILENO);
		close(son->fd_in);
	}
	return (0);
}
int get_redirect(t_son *son, t_token *token)
{
    if (ft_strcmp(token->argument[token->len - 1], ">") == 0)
		mini_redirect(token, son, WRITE);
    if (ft_strcmp(token->argument[1], "<") == 0)
		mini_redirect(token, son, READ);
	return (0);
}
int redirect(t_token *token, t_son *son)
{
    son->pid = fork();
    if (son->pid < 0)
    {
        perror("fork");
        exit (1);
    }
    if (son->pid == 0)
    {
		if (get_redirect(son, token) != 0)
		{
			perror("redirect");
			exit (1);
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