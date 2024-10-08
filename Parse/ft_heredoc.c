/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:00:52 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 19:36:52 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_temp_file(char **temp_filename, int *temp_fd)
{
	*temp_filename = strdup("/tmp/heredocXXXXXX");
	if (!(*temp_filename))
		ft_exit("strdup failed", EXIT_FAILURE);
	*temp_fd = mkstemp(*temp_filename);
	if (*temp_fd == -1)
	{
		free(*temp_filename);
		ft_exit("mkstemp failed", EXIT_FAILURE);
	}
}

void	read_heredoc_content(int temp_fd, char *delimiter)
{
	char	*line;

	line = NULL;
	printf("Enter heredoc (end with '%s'):\n", delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
			break ;
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	if (line == NULL)
		printf("Warning: heredoc ended with EOF (not '%s')\n", delimiter);
	free(line);
}

void	set_heredoc_fd(t_son *son, char *temp_filename)
{
	son->fd_heredoc = open(temp_filename, O_RDONLY);
	if (son->fd_heredoc == -1)
	{
		unlink(temp_filename);
		free(temp_filename);
		ft_exit("open failed", EXIT_FAILURE);
	}
	unlink(temp_filename);
	free(temp_filename);
}

void	handle_heredoc_node(t_node *node, t_son *son)
{
	int		temp_fd;
	char	*temp_filename;

	open_temp_file(&temp_filename, &temp_fd);
	read_heredoc_content(temp_fd, node->right->operation->read);
	close(temp_fd);
	set_heredoc_fd(son, temp_filename);
}

void	handle_heredoc(t_node *node, t_son *son)
{
	if (node == NULL)
		return ;
	handle_heredoc(node->left, son);
	handle_heredoc(node->right, son);
	if (node->operation->type == HEREDOC)
		handle_heredoc_node(node, son);
}
