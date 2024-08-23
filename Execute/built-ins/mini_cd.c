/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:08 by cagarci2          #+#    #+#             */
/*   Updated: 2024/08/22 23:46:08 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mod_env(t_list_env *env, t_token *token, char *flag)
{
	while (env->content != NULL)
	{
		if (flag == "cpwd")
			if (ft_strcmp(env->content, getenv("PWD")))
				env->content = getenv("HOME");
		if (flag == "opwd")
			if (ft_strcmp(env->content, getenv("PWD")))
				env->content = getenv("OLDPWD");
		env = env->next;
	}
	return (0);
}

int	mini_cd(t_list_env *env, t_token *token)
{
	if (ft_strcmp(token->argument[0], "cd") == 0
		|| ft_strcmp(token->argument[0], "cd ~") == 0)
		mod_env(env, token, "cpwd");
	if (ft_strcmp(token->argument[0], "cd -") == 0)
		mod_env(env, token, "opwd");
}
