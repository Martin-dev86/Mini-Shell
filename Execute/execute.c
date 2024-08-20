/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:41:41 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/20 17:58:09 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_token *token, t_son *son)
{
	if (ft_strcmp(token->content, "pwd") == 0)
		mini_pwd(son);
	return (0);
}

int	execute(t_token *token, t_son *son)
{
	if (token->type == BUILTIN)
		execute_builtins(token, son);
	return (0);
}
