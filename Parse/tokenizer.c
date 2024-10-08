/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:56 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 17:58:53 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prev_pointers(t_list_token *head)
{
	t_list_token	*current;
	t_list_token	*prev;

	current = head;
	prev = NULL;
	while (current != NULL)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

//hasta aqui

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


//hasta aqui
void	count_tokens(char *str, int *token_count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			count_quote_tokens(str, &i, token_count);
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<'
			|| str[i] == '\n' || (str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>') || str[i] == '$')
		{
			(*token_count)++;
			i++;
		}
		else if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
		}
		else
		{
			skip_non_token_characters(str, &i);
			(*token_count)++;
		}
	}
}

char	**token_split(t_token *token)
{
	char	*str;
	int		token_count;
	char	**tokens;

	str = token->read;
	token_count = 0;
	count_tokens(str, &token_count);
	tokens = ft_calloc(token_count + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	allocate_tokens(tokens, str);
	return (tokens);
}

t_list_token	*create_next_token_node(t_list_token *current)
{
	current->next = ft_calloc(1, sizeof(t_list_token));
	if (!current->next)
		return (NULL);
	current = current->next;
	current->next = NULL;
	return (current);
}

int	fill_token_list(char **tokens, t_list_token *current)
{
	int		i;
	t_token	*new_token;

	i = 0;
	while (tokens[i])
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			return (0);
		new_token->read = tokens[i];
		current->content = new_token;
		if (tokens[i + 1])
		{
			current = create_next_token_node(current);
			if (!current)
				return (0);
		}
		i++;
	}
	return (1);
}

t_list_token	*token_read_filler(t_token token, t_list_token *head)
{
	char			**tokens;
	t_list_token	*current;

	tokens = token_split(&token);
	if (!tokens)
		return (NULL);
	current = head;
	if (!fill_token_list(tokens, current))
		return (NULL);
	set_prev_pointers(head);
	return (head);
}
