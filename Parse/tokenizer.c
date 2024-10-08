/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:56 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 19:20:29 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
