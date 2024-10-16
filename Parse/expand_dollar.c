/* ************************************************************************** */
/*														*/
/*											:::      ::::::::   */
/*   expand_dollar.c									:+:      :+:    :+:   */
/*									+:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*									+#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:40:30 by jeandrad          #+#    #+#			*/
/*   Updated: 2024/10/04 18:48:43 by cagarci2         ###   ########.fr       */
/*														*/
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable_value(t_processState *state, t_list_shellenv *shellenv)
{
	state->var_value = get_env_value(state->var_name, shellenv);
	if (!state->var_value)
		return ;
	state->var_value_len = ft_strlen(state->var_value);
	if (state->res_index + state->var_value_len >= state->alloc_size)
	{
		state->alloc_size += state->var_value_len + 1;
		state->result = ft_realloc(state->result, state->alloc_size);
		if (!state->result)
			return ;
	}
	ft_strcpy(&state->result[state->res_index], state->var_value);
	state->res_index += state->var_value_len;
}

void	expand_variable(const char *input, t_list_shellenv *shellenv, \
	t_son *son, t_processState *state)
{
	if (input[state->i] == '$' && input[state->i +1] == '?')
	{
		expand_exit_status(son, state);
		state->i += 2;
	}
	else if (input[state->i + 1] == '$')
	{
		state->result[state->res_index++] = '$';
		state->i++;
	}
	else
	{
		extract_variable_name(input, state);
		if (state->var_name[0] != '\0')
			expand_variable_value(state, shellenv);
	}
}

void	process_characters(const char *input, t_processState *state)
{
	if (state->res_index + 1 >= state->alloc_size)
	{
		state->alloc_size += 1;
		state->result = ft_realloc(state->result, state->alloc_size);
		if (!state->result)
			return ;
	}
	state->result[state->res_index++] = input[state->i];
}

void	process_input(const char *input, t_list_shellenv *shellenv, \
	t_son *son, t_processState *state)
{
	state->in_single_quote = false;
	state->in_double_quote = false;
	state->res_index = 0;
	state->i = 0;
	state->len = ft_strlen(input);
	while (state->i < state->len)
	{
		handle_quotes(input, state);
		if (!state->in_single_quote && input[state->i] == '$')
			expand_variable(input, shellenv, son, state);
		else if (input[state->i] != '\'' && input[state->i] != '"')
			process_characters(input, state);
		state->i++;
	}
	state->result[state->res_index] = '\0';
	if (state->in_single_quote || state->in_double_quote)
	{
		free(state->result);
		state->result = NULL;
	}
}

char	*replace_variables(const char *input, \
	t_list_shellenv *shellenv, t_son *son)
{
	size_t			len;
	size_t			alloc_size;
	char			*result;
	t_processState	state;

	len = ft_strlen(input);
	alloc_size = len + 1;
	result = ft_calloc(alloc_size, sizeof(char));
	if (!result)
		return (NULL);
	ft_memset(&state, 0, sizeof(t_processState));
	state.alloc_size = alloc_size;
	state.result = result;
	if (count_quotes(input) == 0)
		return (ft_strdup(""));
	else
		process_input(input, shellenv, son, &state);
	return (state.result);
}
