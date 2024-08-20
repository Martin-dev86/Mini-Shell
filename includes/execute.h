/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:52 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 13:07:12 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define READ_END = 0;
#define WRITE_END = 1;
typedef struct s_pipe
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		fd[2];
}	t_pipe;

