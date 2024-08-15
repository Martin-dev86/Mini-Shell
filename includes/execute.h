/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:52 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/15 16:14:04 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
# define READ_END = 0;
# define WRITE_END = 1;

typedef struct s_execute
{
    pid_t   pid;
    int     fd_in;
    int     fd_out;
    int     fd[2];
} t_execute;