/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:56 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 17:40:19 by jeandrad         ###   ########.fr       */
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

void	print_token_links(t_list_token *head)
{
	t_list_token	*current;

	current = head;
	while (current != NULL)
		current = current->next;
}

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

void	handle_quotes1(char **tokens, char *str, int *i, int *j, char quote)
{
	(*i)++;
	tokens[*j] = quote_catcher(str, i, quote);
	if (tokens[*j] == NULL)
		return ;
	(*j)++;
}

void	handle_operator(char **tokens, char *op, int *j)
{
	tokens[*j] = strdup(op);
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

void	handle_special_operator(char **tokens, char *str, int *i, int *j)
{
	if (str[*i] == '|')
		handle_operator(tokens, "|", j);
	else if (str[*i] == '$')
		handle_operator(tokens, "$", j);
	else if (str[*i] == '\n')
		handle_operator(tokens, "\n", j);
	(*i)++;
}

void	handle_redirection_operator(char **tokens, char *str, int *i, int *j)
{
	if (str[*i] == '>')
	{
		handle_operator(tokens, ">>", j);
	}
	else
	{
		handle_operator(tokens, "<<", j);
	}
	(*i) += 2;
}

void	handle_single_redirection_operator(char **tokens, char *str, int *i,
		int *j)
{
	if (str[*i] == '>')
	{
		handle_operator(tokens, ">", j);
	}
	else
	{
		handle_operator(tokens, "<", j);
	}
	(*i)++;
}

void	allocate_tokens(char **tokens, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			handle_quotes1(tokens, str, &i, &j, str[i]);
		else if (str[i] == '|' || str[i] == '$' || str[i] == '\n')
			handle_special_operator(tokens, str, &i, &j);
		else if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
				+ 1] == '<'))
			handle_redirection_operator(tokens, str, &i, &j);
		else if (str[i] == '>' || str[i] == '<')
			handle_single_redirection_operator(tokens, str, &i, &j);
		else if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
		}
		else
			handle_token(tokens, str, &i, &j);
	}
	tokens[j] = NULL;
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
