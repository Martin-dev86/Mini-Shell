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

<<<<<<< HEAD
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
=======
int	mini_cd(t_token *token, t_list_env *env)
{
	t_list_env	*current;
	char		*temp;
	int			i;

	i = 0;
	env->len = 0;
	current = env;
	while (token->argument[env->len])
		env->len++;
	if (env->len == 1)
	{
		while (current && current->next)
		{
			env->variable_len = mini_strlen(current->content);
			env->len = env->variable_len;
			if (ft_strncmp(current->content, "USER=", env->variable_len) == 0)
			{
				while (current->content[env->len])
				{
					temp[i] = current->content[env->len];
					i++;
					env->len++;
				}
				temp = ft_strjoin("/home/", temp);
				//printf("%s\n", temp);
			}
			current = current->next;
		}
		current = env;
		while (current && current->next)
		{
			env->variable_len = mini_strlen(current->content);
			env->len = env->variable_len;
			if (ft_strncmp(current->content, "PWD=", env->variable_len) == 0)
				chdir(temp);
			current = current->next;
		}
	}
	current = env;
	while (current && current->next)
	{
		env->variable_len = mini_strlen(current->content);
		if (ft_strncmp(current->content, "PWD=", env->variable_len) == 0)
			temp = current->content;
		if (ft_strncmp(current->content, "OLDPWD=", env->variable_len) == 0)
			chdir(temp);
		current = current->next;
	}
	if (!token->argument[1])
		return (1);
	if (chdir(token->argument[1]) == -1)
	{
		perror("cd");
		return (1);
	}
return (0);
>>>>>>> origin/Master
}
