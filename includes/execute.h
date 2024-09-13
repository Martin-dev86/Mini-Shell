/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:52 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/13 18:41:36 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define READ  0
#define WRITE  1

typedef struct s_son
{
	pid_t	pid;
	int		**fd;
	int		code;
	int		fd_in;
	int		fd_out;
}	t_son;

typedef struct s_exec_args
{
	t_token		*token;
	t_son		*son;
	t_list_env	*env;
	t_node		*node;
}	t_exec_args;