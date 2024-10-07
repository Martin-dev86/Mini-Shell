/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:56 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/08 01:00:30 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prev_pointers(t_list_token *head)
{
	t_list_token *current;
	t_list_token *prev;

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
	t_list_token *current;

	current = head;
	while (current != NULL)
	{
		// Uncomment the following line to print the token links
		// printf("Token: %s, Previous: %s, Next: %s\n", current->content->read,
		//    current->prev ? current->prev->content->read : "NULL",
		//    current->next ? current->next->content->read : "NULL");
		current = current->next;
	}
}

char	*quote_catcher(char *str, int *i, int quote)
{
	char temp[2] = {str[*i], '\0'};
	char *new_result;
	char *result = strdup("");

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
void handle_quotes1(char **tokens, char *str, int *i, int *j, char quote) {
    (*i)++;
    tokens[*j] = quote_catcher(str, i, quote);
    if (tokens[*j] == NULL) return;
    (*j)++;
}

void handle_operator(char **tokens, char *op, int *j) {
    tokens[*j] = strdup(op);
    if (tokens[*j] == NULL) return;
    (*j)++;
}

void handle_token(char **tokens, char *str, int *i, int *j) {
    int start = *i;
    while (str[*i] && str[*i] != 34 && str[*i] != 39 && str[*i] != '|'
           && str[*i] != '>' && str[*i] != '<' && str[*i] != '$'
           && str[*i] != '\n' && str[*i] != ' ') {
        (*i)++;
    }
    tokens[*j] = strndup(str + start, *i - start);
    if (tokens[*j] == NULL) return;
    (*j)++;
}

void allocate_tokens(char **tokens, char *str) {
	int i = 0, j = 0;

	while (str[i]) {
		if (str[i] == 34 || str[i] == 39) {
			handle_quotes1(tokens, str, &i, &j, str[i]);
		} else if (str[i] == '|' || str[i] == '$' || str[i] == '\n') {
			handle_operator(tokens, (str[i] == '|') ? "|" : (str[i] == '$') ? "$" : "\n", &j);
			i++;
		} else if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) {
			handle_operator(tokens, (str[i] == '>') ? ">>" : "<<", &j);
			i += 2;
		} else if (str[i] == '>' || str[i] == '<') {
			handle_operator(tokens, (str[i] == '>') ? ">" : "<", &j);
			i++;
		} else if (str[i] == ' ') {
			while (str[i] == ' ') i++;
		} else
			handle_token(tokens, str, &i, &j);
	}
	tokens[j] = NULL;
}

void count_tokens(char *str, int *token_count) {
    int i = 0;
    int quote;

    while (str[i]) {
        if (str[i] == 34 || str[i] == 39) {
            quote = str[i];
            i++;
            while (str[i] && str[i] != quote)
                i++;
            if (str[i] == quote)
                i++;
            (*token_count)++;
        } else if (str[i] == '|' || str[i] == '>' || str[i] == '<'
                || str[i] == '\n' || (str[i] == '<' && str[i + 1] == '<')
                || (str[i] == '>' && str[i + 1] == '>') || str[i] == '$') {
            (*token_count)++;
            i++;
        } else if (str[i] == ' ') {
            while (str[i] == ' ')
                i++;
        } else {
            while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|'
                    && str[i] != '>' && str[i] != '<' && str[i] != '$'
                    && str[i] != '\n' && str[i] != ' ')
                i++;
            (*token_count)++;
        }
    }
}

char **token_split(t_token *token)
{
    char *str = token->read;
    int token_count = 0;
    char **tokens;

    count_tokens(str, &token_count);
    tokens = ft_calloc(token_count + 1, sizeof(char *));
    if (!tokens)
        return NULL;
    allocate_tokens(tokens, str);
    return tokens;
}

t_list_token	*token_read_filler(t_token token, t_list_token *head)
{
	int				i;
	char			**tokens;
	t_list_token	*current;
	t_token			*new_token;

	tokens = token_split(&token);
	if (!tokens)
		return NULL;
	current = head;
	i = 0;
	while (tokens[i])
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			return NULL;
		new_token->read = tokens[i];
		current->content = new_token;
		if (tokens[i + 1])
		{
			current->next = ft_calloc(1, sizeof(t_list_token));
			if (!current->next)
				return (NULL); 
			current = current->next;
			current->next = NULL;
		}
		i++;
	}
	set_prev_pointers(head);
	return (head);
}

// // Function to set the prev pointers in the linked list
// void	set_prev_pointers(t_list_token *head)
// {
// 	t_list_token *current;
// 	t_list_token *prev;

// 	current = head;
// 	prev = NULL;
// 	while (current != NULL)
// 	{
// 		current->prev = prev;
// 		prev = current;
// 		current = current->next;
// 	}
// }

// void	print_token_links(t_list_token *head)
// {
// 	t_list_token *current;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		// Uncomment the following line to print the token links
// 		// printf("Token: %s, Previous: %s, Next: %s\n", current->content->read,
// 		//    current->prev ? current->prev->content->read : "NULL",
// 		//    current->next ? current->next->content->read : "NULL");
// 		current = current->next;
// 	}
// }

// // Function to handle quotes and capture everything inside them
// char	*quote_catcher(char *str, int *i, int quote)
// {
// 	char temp[2] = {str[*i], '\0'};
// 	char *new_result;
// 	char *result = strdup(""); // Start with an empty string

// 	//printf("Entering quote_catcher with str: %s, i: %d, quote: %c\n", str, *i, quote);

// 	while (str[*i] && str[*i] != quote)
// 	{
// 		temp[0] = str[*i];
// 		new_result = ft_strjoin(result, temp);
// 		free(result);
// 		result = new_result;
// 		(*i)++;
// 	}

// 	// If the closing quote is found, skip it
// 	if (str[*i] == quote)
// 		(*i)++; // Skip the closing quote

// 	printf("Exiting quote_catcher with result: %s, i: %d\n", result, *i);
// 	return (result);
// }

// char	**token_split(t_token *token)
// {
// 	char	*str;
// 	int		i, j;
// 	int		token_count;
// 	int		quote;
// 	char	**tokens;
// 	int		start;

// 	str = token->read;
// 	i = 0, j = 0;
// 	token_count = 0;

// 	// First pass to count the number of tokens
// 	while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39) 
// 		{
// 			quote = str[i];
// 			i++;
// 			while (str[i] && str[i] != quote)
// 				i++;
// 			if (str[i] == quote)
// 				i++;
// 			token_count++;
// 		}
// 		else if (str[i] == '|' || str[i] == '>' || str[i] == '<'
// 			|| str[i] == '\n' || (str[i] == '<' && str[i + 1] == '<')
// 			|| (str[i] == '>' && str[i + 1] == '>') || str[i] == '$')
// 		{
// 			token_count++;
// 			i++;
// 		}
// 		else if (str[i] == ' ')
// 		{
// 			while (str[i] == ' ')
// 				i++; // Skip consecutive spaces
// 		}
// 		else
// 		{
// 			while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|'
// 				&& str[i] != '>' && str[i] != '<' && str[i] != '$'
// 				&& str[i] != '\n' && str[i] != ' ')
// 				i++;
// 			token_count++;
// 		}
// 	}

// 	// Allocate memory for the array of tokens
// 	tokens = ft_calloc(token_count + 1, sizeof(char *));
// 	if (!tokens)
// 		return (NULL);

// 	// Second pass to populate the array of tokens
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 34)
// 		{
// 			i++;
// 			tokens[j] = quote_catcher(str, &i, 34);
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return NULL; // Handle memory allocation failure
// 			j++;
// 		}
// 		else if (str[i] == 39)
// 		{
// 			i++;
// 			tokens[j] = quote_catcher(str, &i, 39);
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return NULL; // Handle memory allocation failure
// 			j++;
// 		}
// 		else if (str[i] == '|')
// 		{
// 			tokens[j] = strdup("|");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return (NULL); // Handle memory allocation failure
// 			j++;
// 			i++;
// 		}
// 		else if (str[i] == '>' && str[i + 1] == '>')
// 		{
// 			tokens[j] = strdup(">>");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return NULL; // Handle memory allocation failure
// 			j++;
// 			i += 2;
// 		}
// 		else if (str[i] == '<' && str[i + 1] == '<')
// 		{
// 			tokens[j] = strdup("<<");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return NULL; // Handle memory allocation failure
// 			j++;
// 			i += 2;
// 		}
// 		else if (str[i] == '>')
// 		{
// 			tokens[j] = strdup(">");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return (NULL); // Handle memory allocation failure
// 			j++;
// 			i++;
// 		}
// 		else if (str[i] == '<')
// 		{
// 			tokens[j] = strdup("<");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return NULL; // Handle memory allocation failure
// 			j++;
// 			i++;
// 		}
// 		else if (str[i] == '$')
// 		{
// 			tokens[j] = strdup("$");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return (NULL); // Handle memory allocation failure
// 			j++;
// 			i++;
// 		}
// 		else if(str[i] == '\n')
// 		{
// 			tokens[j] = strdup("\n");
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return NULL; // Handle memory allocation failure
// 			j++;
// 			i++;
// 		}
// 		else if (str[i] == ' ') {
// 			while (str[i] == ' ')
// 				i++; // Skip consecutive spaces
// 		}
// 		else 
// 		{
// 			start = i;
// 			while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|'
// 				&& str[i] != '>' && str[i] != '<' && str[i] != '$'
// 				&& str[i] != '\n' && str[i] != ' ')
// 				i++;
// 			tokens[j] = strndup(str + start, i - start);
// 			//printf("Token: %s\n", tokens[j]);
// 			if (tokens[j] == NULL)
// 				return (NULL); // Handle memory allocation failure
// 			j++;
// 		}
// 	}
// 	tokens[j] = NULL; // Null-terminate the token array
// 	return (tokens);
// }

// t_list_token	*token_read_filler(t_token token, t_list_token *head)
// {
// 	int				i;
// 	char			**tokens;
// 	t_list_token	*current;
// 	t_token			*new_token;

// 	tokens = token_split(&token);
// 	if (!tokens)
// 		return NULL; // Handle memory allocation failure

// 	current = head;
// 	// Put the tokens in the array to the list for easier work of the DFA
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		new_token = ft_calloc(1, sizeof(t_token));
// 		if (!new_token)
// 			return NULL; // Handle memory allocation failure
// 		new_token->read = tokens[i];
// 		current->content = new_token;
// 		//printf("Token content: %s\n", new_token->read);
// 		if (tokens[i + 1])
// 		{
// 			current->next = ft_calloc(1, sizeof(t_list_token));
// 			if (!current->next)
// 				return (NULL); 
// 			current = current->next;
// 			current->next = NULL;
// 		}
// 		i++;
// 	}
// 	set_prev_pointers(head);
// 	//print_token_links(head);
// 	return (head);
// }

