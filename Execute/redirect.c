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

int mini_redirect(t_token *token, t_son *son)
{
	int i;

	i = 0;
	while(i < token->len)
	{	
		if (ft_strcmp(token->argument[i], ">") == 0)
		{
			son->fd_out = open(token->argument[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (son->fd_out < 0)
			{
				perror("output");
				exit (1);
			}
			dup2(son->fd_out, STDOUT_FILENO);
			close(son->fd_out);
		}
		else if (ft_strcmp(token->argument[i], "<") == 0)
		{
			son->fd_in = open(token->argument[i - 1], O_RDONLY);
			if (son->fd_in < 0)
			{
				perror("input");
				exit (1);
			}
			dup2(son->fd_in, STDIN_FILENO);
			close(son->fd_in);
		}
		i++;
	}
	return (0);
}
// int		count;
// 	char	buffer[1024];
// if(son->fd_in != STDIN_FILENO)
// 		{
// 			while ((count = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0)
//             {	
// 				buffer[count] = '\0';
// 				printf("%s", buffer);
// 			}
//         	if (count < 0)
//         	{
//             	perror("read");
//             	return (1);
//         	}