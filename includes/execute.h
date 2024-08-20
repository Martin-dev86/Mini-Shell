/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:52 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 17:46:54 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define READ_END = 0;
#define WRITE_END = 1;

typedef struct s_son
{
	pid_t	pid;
	int		fd_read;
	int		fd_write;
	int		fd[2];
}	t_son;


