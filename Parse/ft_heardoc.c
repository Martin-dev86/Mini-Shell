/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heardoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:00:52 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/03 20:46:16 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_node *node)
{
    char	*line;
    size_t	len;
    ssize_t	read;
    int		temp_fd;
    char	*temp_filename;

    if (node == NULL)
        return ;
    handle_heredoc(node->left);
    handle_heredoc(node->right);
    if (node->operation->type == HEREDOC)
    {
        line = NULL;
        len = 0;
        temp_filename = strdup("/tmp/heredocXXXXXX");
        if (!temp_filename)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        // Create a unique temporary file
        temp_fd = open(temp_filename, O_CREAT | O_RDWR | O_EXCL, 0600);
        if (temp_fd == -1)
        {
            perror("open");
            free(temp_filename);
            exit(EXIT_FAILURE);
        }

        printf("Enter heredoc (end with '%s'):\n", node->operation->read);
        while ((line = readline("> ")) != NULL)
        {
            if (strcmp(line, node->operation->read) == 0)
                break ;
            write(temp_fd, line, strlen(line));
            write(temp_fd, "\n", 1);
            free(line);
        }
        free(line);
        close(temp_fd);
        node->fd = open(temp_filename, O_RDONLY);
    	unlink(temp_filename);
        free(temp_filename);
    }
}