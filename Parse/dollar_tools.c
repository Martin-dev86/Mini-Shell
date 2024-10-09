/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:29:39 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 19:33:24 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *key, t_list_shellenv *shellenv)
{
	size_t		key_len;
	t_list_env	*current;

	key_len = ft_strlen(key);
	current = shellenv->env;
	while (current)
	{
		if (ft_strncmp(current->content, key, key_len) == 0
			&& current->content[key_len] == '=')
		{
			return (current->content + key_len + 1);
		}
		current = current->next;
	}
	return (NULL);
}

void	print_env(t_list_shellenv *shellenv)
{
	t_list_env	*current;

	current = shellenv->env;
	printf("Variables de entorno:\n");
	while (current)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

void	handle_quotes(const char *input, t_processState *state)
{
	if (input[state->i] == '\'' && !state->in_double_quote)
	{
		state->in_single_quote = !state->in_single_quote;
		state->result[state->res_index++] = input[state->i];
	}
	else if (input[state->i] == '"' && !state->in_single_quote)
	{
		state->in_double_quote = !state->in_double_quote;
		state->result[state->res_index++] = input[state->i];
	}
}

void	expand_exit_status(t_son *son, t_processState *state)
{
	state->exit_status = ft_itoa(son->code);
	if (state->exit_status)
	{
		state->exit_len = ft_strlen(state->exit_status);
		if (state->res_index + state->exit_len >= state->alloc_size)
		{
			state->alloc_size += state->exit_len + 1;
			state->result = ft_realloc(state->result, state->alloc_size);
			if (!state->result)
				return ;
		}
		ft_strcpy(&state->result[state->res_index], state->exit_status);
		state->res_index += state->exit_len;
		free(state->exit_status);
	}
}
