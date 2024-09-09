/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:56 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/09 17:27:09 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to set the prev pointers in the linked list
void set_prev_pointers(t_list_token *head)
{
    t_list_token *current = head;
    t_list_token *prev = NULL;

    while (current != NULL)
    {
        current->prev = prev;
        prev = current;
        current = current->next;
    }
}

void print_token_links(t_list_token *head)
{
    t_list_token *current = head;
    while (current != NULL)
    {
        printf("Token: %s, Previous: %s, Next: %s\n",
               current->content->read,
               current->prev ? current->prev->content->read : "NULL",
               current->next ? current->next->content->read : "NULL");
        current = current->next;
    }
}

//NEW PROBLEM with the quotes, SEG FAULT

char *quote_catcher(char *str, int *i, int quote)
{
    char *result = NULL;
    while (str[*i] && str[*i] != quote)
    {
        char temp[2] = {str[*i], '\0'};
        result = ft_strjoin(result, temp);
        (*i)++;
    }
    // If the closing quote is not found, return the partial result
    if (str[*i] == quote)
    {
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
            token_count++;
        } 
        else if (str[i] == '|' || str[i] == '>' || str[i] == '<' ||
                 str[i] == '\n' || (str[i] == '<' && str[i + 1] == '<') ||
                 (str[i] == '>' && str[i + 1] == '>') || str[i] == '$') 
        {
            token_count++;
            i++;
        } 
        else if (str[i] == ' ') 
        {
            while (str[i] == ' ') i++; // Skip consecutive spaces
        }
        else 
        {
            while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '$' && str[i] != '\n' && str[i] != ' ') 
                i++;
            token_count++;
        }
    }

    // Allocate memory for the array of tokens
    char **tokens = ft_calloc(token_count + 1, sizeof(char *));
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
            printf("Token: %s\n", tokens[j]);
            if (tokens[j] == NULL)
                return NULL; // Handle memory allocation failure
            j++;
        } 
        else if (str[i] == 39) 
        { // ASCII code for '
            i++;
            tokens[j] = quote_catcher(str, &i, 39);
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
        } 
        else if (str[i] == '|')
        {
            tokens[j] = strdup("|");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i++;
        } 
        else if (str[i] == '>' && str[i + 1] == '>')
        {
            tokens[j] = strdup(">>");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i += 2;
        }
        else if (str[i] == '>') 
        {
            tokens[j] = strdup(">");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i++;
        } 
        else if (str[i] == '<') 
        {
            tokens[j] = strdup("<");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i++;
        } 
        else if (str[i] == '$') 
        {
            tokens[j] = strdup("$");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i++;
        }
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            tokens[j] = strdup("<<");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i += 2;
        }
        else if (str[i] == '\n') 
        {
            tokens[j] = strdup("\n");
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
            i++;
        } 
        else if (str[i] == ' ') 
        {
            while (str[i] == ' ') i++; // Skip consecutive spaces
        }
        else 
        {
            int start = i;
            while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '$' && str[i] != '\n' && str[i] != ' ') i++;
            tokens[j] = strndup(str + start, i - start);
            if (tokens[j] == NULL) return NULL; // Handle memory allocation failure
            j++;
        }
    }
    tokens[j] = NULL; // Null-terminate the token array
    return (tokens);
}

t_list_token *token_read_filler(t_token token, t_list_token *head)
{
    int i;
    char **tokens = token_split(&token);
    if (!tokens) return NULL; // Handle memory allocation failure
    t_list_token *current = head;
    
    // Put the tokens in the array to the list for easier work of the DFA
    i = 0;
    while (tokens[i]) 
    {
        t_token *new_token = ft_calloc(1, sizeof(t_token));
        if (!new_token)
            return NULL; // Handle memory allocation failure
        new_token->read = tokens[i];
        current->content = new_token;
        
        if (tokens[i + 1]) 
        {
            current->next = ft_calloc(1, sizeof(t_list_token));
            if (!current->next)
                return NULL; // Handle memory allocation failure
            current = current->next;
            current->next = NULL;
        }
        
        i++;
    }
    set_prev_pointers(head);
    print_token_links(head);
    return (head);
}