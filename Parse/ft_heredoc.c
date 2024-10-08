/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:00:52 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 23:50:01 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_temp_file(char **temp_filename, int *temp_fd)
{
	*temp_filename = strdup("/tmp/heredocXXXXXX");
	if (!(*temp_filename))
		ft_exit("strdup failed", EXIT_FAILURE);
	*temp_fd = open(*temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*temp_fd == -1)
	{
		free(*temp_filename);
		ft_exit("mkstemp failed", EXIT_FAILURE);
	}
}

void	process_heredoc_content(t_node *node, int temp_fd)
{
	char	*line;

	printf("Enter heredoc (end with '%s'):\n", node->right->operation->read);
	line = readline("> ");
	while (line != NULL)
	{
		if (strcmp(line, node->right->operation->read) == 0)
			break ;
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line == NULL)
		printf("Warning: heredoc ended with EOF (not '%s')\n",
			node->right->operation->read);
	free(line);
}

void	handle_heredoc(t_node *node, t_son *son)
{
	char	*temp_filename;
	char buffer[256] = {0};
	
	if (node == NULL)
		return ;
	handle_heredoc(node->left, son);
	handle_heredoc(node->right, son);
	if (node->operation->type == HEREDOC)
	{
		create_temp_file(&temp_filename, &node->temp_fd);
		process_heredoc_content(node, node->temp_fd);
		close(node->temp_fd);
		son->fd_heredoc = open(temp_filename, O_RDONLY);
		if (son->fd_heredoc == -1)
		{
			unlink(temp_filename);
			free(temp_filename);
			ft_exit("open failed", EXIT_FAILURE);
		}
		while (read(son->fd_heredoc, buffer, sizeof(buffer)) > 0)
            write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		close(son->fd_heredoc);
		unlink(temp_filename);
		free(temp_filename);
	}
}
