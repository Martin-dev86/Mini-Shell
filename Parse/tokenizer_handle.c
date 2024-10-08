/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:58:58 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 17:59:35 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_catcher(char *str, int *i, int quote)
{
	char	temp[2];
	char	*new_result;
	char	*result;

	temp[0] = str[*i];
	temp[1] = '\0';
	result = strdup("");
	while (str[*i] && str[*i] != quote)
	{
		temp[0] = str[*i];
		new_result = ft_strjoin(result, temp);
		free(result);
		result = new_result;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	return (result);
}

void	handle_quotes1(char **tokens, char *str, t_token_counters *counters,
		char quote)
{
	counters->i++;
	tokens[counters->j] = quote_catcher(str, &counters->i, quote);
	if (tokens[counters->j] == NULL)
		return ;
	counters->j++;
}

void	handle_operator(char **tokens, char *op, int *j)
{
	tokens[*j] = ft_strdup(op);
	if (tokens[*j] == NULL)
		return ;
	(*j)++;
}

void	handle_token(char **tokens, char *str, int *i, int *j)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != 34 && str[*i] != 39 && str[*i] != '|'
		&& str[*i] != '>' && str[*i] != '<' && str[*i] != '$' && str[*i] != '\n'
		&& str[*i] != ' ')
		(*i)++;
	tokens[*j] = strndup(str + start, *i - start);
	if (tokens[*j] == NULL)
		return ;
	(*j)++;
}


void	handle_special_operator(char **tokens, char *str,
		t_token_counters *counters)
{
	if (str[counters->i] == '|')
		handle_operator(tokens, "|", &counters->j);
	else if (str[counters->i] == '$')
		handle_operator(tokens, "$", &counters->j);
	else if (str[counters->i] == '\n')
		handle_operator(tokens, "\n", &counters->j);
	counters->i++;
}
