/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:04:25 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 18:04:36 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_operator(char **tokens, char *str,
		t_token_counters *counters)
{
	if (str[counters->i] == '>')
	{
		handle_operator(tokens, ">>", &counters->j);
	}
	else
	{
		handle_operator(tokens, "<<", &counters->j);
	}
	counters->i += 2;
}

void	handle_single_redirection_operator(char **tokens, char *str,
		t_token_counters *counters)
{
	if (str[counters->i] == '>')
	{
		handle_operator(tokens, ">", &counters->j);
	}
	else
	{
		handle_operator(tokens, "<", &counters->j);
	}
	counters->i++;
}

void	allocate_tokens(char **tokens, char *str)
{
	t_token_counters	counters;

	counters.i = 0;
	counters.j = 0;
	while (str[counters.i])
	{
		if (str[counters.i] == 34 || str[counters.i] == 39)
			handle_quotes1(tokens, str, &counters, str[counters.i]);
		else if (str[counters.i] == '|' || str[counters.i] == '$'
			|| str[counters.i] == '\n')
			handle_special_operator(tokens, str, &counters);
		else if ((str[counters.i] == '>' && str[counters.i + 1] == '>')
			|| (str[counters.i] == '<' && str[counters.i + 1] == '<'))
			handle_redirection_operator(tokens, str, &counters);
		else if (str[counters.i] == '>' || str[counters.i] == '<')
			handle_single_redirection_operator(tokens, str, &counters);
		else if (str[counters.i] == ' ')
		{
			while (str[counters.i] == ' ')
				counters.i++;
		}
		else
			handle_token(tokens, str, &counters.i, &counters.j);
	}
	tokens[counters.j] = NULL;
}

void	count_quote_tokens(char *str, int *i, int *token_count)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	(*token_count)++;
}

void	skip_non_token_characters(char *str, int *i)
{
	while (str[*i] && str[*i] != 34 && str[*i] != 39 && str[*i] != '|'
		&& str[*i] != '>' && str[*i] != '<' && str[*i] != '$' && str[*i] != '\n'
		&& str[*i] != ' ')
	{
		(*i)++;
	}
}
