/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:21:19 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 15:12:32 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *quote_catcher(char *str, int *i, int quote)
{
    char *result = NULL;
    while (str[*i] && str[*i] != quote) {
        char temp[2] = {str[*i], '\0'};
        result = ft_strjoin(result, temp);
        (*i)++;
    }
    if (str[*i] == quote) {
        (*i)++; // Skip the closing quote
    }
    return result;
}

char **token_split(t_token *token) 
{
    char *str = token->read;
    int i = 0, j = 0;
    int token_count = 0;

    // First pass to count the number of tokens
    while (str[i]) 
    {
        if (str[i] == 34 || str[i] == 39) 
        { // ASCII code for " or '
            int quote = str[i];
            i++;
            while (str[i] && str[i] != quote) i++;
            if (str[i] == quote) i++;
        } 
        else if (str[i] == '|' || str[i] == '>' || str[i] == '<' ||
                 str[i] == '\n' || (str[i] == '<' && str[i + 1] == '<') ||
                 (str[i] == '>' && str[i + 1] == '>') || str[i] == '$') 
        {
            token_count++;
            i++;
        } 
        else 
        {
            while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\n') 
                i++;
            token_count++;
        }
    }

    // Allocate memory for the array of tokens
    char **tokens = malloc((token_count + 1) * sizeof(char *));
    if (!tokens) 
        return NULL;

    // Second pass to populate the array of tokens
    i = 0;
    while (str[i]) 
    {
        if (str[i] == 34) 
        { // ASCII code for "
            i++;
            tokens[j] = quote_catcher(str, &i, 34);
            j++;
        } 
        else if (str[i] == 39) 
        { // ASCII code for '
            i++;
            tokens[j] = quote_catcher(str, &i, 39);
            j++;
        } 
        else if (str[i] == '|')
        {
            tokens[j] = strdup("|");
            j++;
            i++;
        } 
        else if (str[i] == '>') 
        {
            tokens[j] = strdup(">");
            j++;
            i++;
        } 
        else if (str[i] == '<') 
        {
            tokens[j] = strdup("<");
            j++;
            i++;
        } 
        else if (str[i] == '$') 
        {
            tokens[j] = strdup("$");
            j++;
            i++;
        }
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            tokens[j] = strdup("<<");
            j++;
            i += 2;
        }
        else if (str[i] == '>' && str[i + 1] == '>')
        {
            tokens[j] = strdup(">>");
            j++;
            i += 2;
        }
        else if (str[i] == '\n') 
        {
            tokens[j] = strdup("\n");
            j++;
            i++;
        } 
        else 
        {
            int start = i;
            while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '$' && str[i] != '\n') i++;
            tokens[j] = strndup(str + start, i - start);
            j++;
        }
    }
    tokens[j] = NULL; // Null-terminate the token array
    return (tokens);
}// Gives the split read to each token for typing


t_list_token *token_read_filler(t_token token, t_list_token *head)
{
    int i;
    char **tokens = token_split(&token);
    t_list_token *current = head;
    
    // Put the tokens in the array to the list for easier work of the DFA
    i = 0;
    while (tokens[i]) 
    {
        t_token *new_token = malloc(sizeof(t_token));
        if (!new_token)
            return NULL; // Handle memory allocation failure
        new_token->read = tokens[i];
        current->content = new_token;
        
        if (tokens[i + 1]) {
            current->next = malloc(sizeof(t_list_token));
            if (!current->next)
                return NULL; // Handle memory allocation failure
            current = current->next;
            current->next = NULL;
        }
        i++;
    }
    return head;
}