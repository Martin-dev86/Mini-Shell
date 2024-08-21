/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:52 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/21 10:19:55 by cagarci2         ###   ########.fr       */
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
	int		code;
}	t_son;


