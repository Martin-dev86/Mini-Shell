/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:52 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/07 18:00:20 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define READ  0
#define WRITE  1

typedef struct s_son
{
	pid_t	*pids;
	pid_t	pid;
	int		**fd;
	int		code;
	int		fd_in;
	int		fd_out;
	int		fd_heredoc;
	int		flag;
	int		i;
	int		g_interrupted;
}	t_son;
