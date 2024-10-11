/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:29:39 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/11 10:27:32 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *key, t_list_shellenv *shellenv)
{
	size_t		key_len;
	t_list_env	*current;
	char		*delimiter_position;

	key_len = ft_strlen(key);
	current = shellenv->env;
	while (current)
	{
		delimiter_position = ft_strchr(current->content, '=');
		if (delimiter_position)
		{
			if ((size_t)(delimiter_position - current->content) == key_len &&
				ft_strncmp(current->content, key, key_len) == 0)
			{
				return (delimiter_position + 1);
			}
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

void	extract_variable_name(const char *input, t_processState *state)
{
	state->var_start = ++state->i;
	while (state->i < state->len && \
		(ft_isalnum(input[state->i]) || input[state->i] == '_'))
		state->i++;
	if (state->i == state->var_start)
	{
		state->result[state->res_index++] = '$';
		return ;
	}
	ft_strlcpy(state->var_name, &input[state->var_start], \
		state->i - state->var_start + 1);
	state->i--;
}
