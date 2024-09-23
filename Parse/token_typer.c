/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_typer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:50:05 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 17:23:26 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// This function will determine the type of token_list
void token_list_typer (t_list_token *token_list) {    
    t_list_token *head = token_list;

    while(token_list) {    
        if (ft_strcmp(token_list->content->read, "|") == 0) {
            token_list->content->type = PIPE;
            token_list->content->priority = 1;
        } else if (ft_strcmp(token_list->content->read, ">") == 0) {
            token_list->content->type = REDIR_R;
            token_list->content->priority = 2;
        } else if (ft_strcmp(token_list->content->read, "<") == 0) {
            token_list->content->type = REDIR_L;
            token_list->content->priority = 2;
        } else if (ft_strcmp(token_list->content->read, ">>") == 0) {
            token_list->content->type = APPEND;
            token_list->content->priority = 4;
        } else if (ft_strcmp(token_list->content->read, "<<") == 0) {
            token_list->content->type = HEREDOC;
            token_list->content->priority = 4;
        } else if (ft_strcmp(token_list->content->read, "\n") == 0) {
            token_list->content->type = ENDLINE;
            token_list->content->priority = 3;
        } else {
            token_list->content->type = CMD;
            token_list->content->priority = 3;
        }
        token_list = token_list->next;
    }
    token_list = head;
}
