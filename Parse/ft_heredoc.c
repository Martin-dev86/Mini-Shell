/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:00:52 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/03 23:04:51 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_node *node, t_son *son)
{
    char	*line;
    int		temp_fd;
    char	*temp_filename;

    if (node == NULL)
        return ;
    handle_heredoc(node->left, son);
    handle_heredoc(node->right, son);
    if (node->operation->type == HEREDOC)
    {
        line = NULL;
        //len = 0;
        temp_filename = strdup("/tmp/heredocXXXXXX");
        if (!temp_filename)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        temp_fd = mkstemp(temp_filename);
        if (temp_fd == -1)
        {
            perror("open");
            free(temp_filename);
            exit(EXIT_FAILURE);
        }

        printf("Enter heredoc (end with '%s'):\n", node->right->operation->read);
        while ((line = readline("> ")) != NULL)
        {
            if (strcmp(line, node->right->operation->read) == 0)
                break ;
            write(temp_fd, line, strlen(line));
            write(temp_fd, "\n", 1);
            free(line);
        }
        if (line == NULL)
            printf("Warning: heredoc ended with EOF (not '%s')\n", node->right->operation->read);
        close(temp_fd);
        son->fd_heredoc = open(temp_filename, O_RDONLY);
        if (son->fd_heredoc == -1)
        {
            perror("open");
            unlink(temp_filename);
            free(temp_filename);
            exit(EXIT_FAILURE);
        }

        unlink(temp_filename);
        free(temp_filename);
    }
}