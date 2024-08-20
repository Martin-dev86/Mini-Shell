/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:38:01 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 17:59:10 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/wait.h>
# include <memory.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "execute.h"
# include "parse.h"

char	*get_pwd(void);
int		mini_pwd(t_son *son);
int		execute(t_token *token, t_son *son);
int		execute_builtins(t_token *token, t_son *son);
#endif