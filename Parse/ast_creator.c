/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:57:35 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/18 20:32:53 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Función para crear un nuevo nodo AST
t_node *create_ast_node(t_token *operation) {
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node) {
        ft_exit("Memory allocation failed for AST node", 1);
    }
    node->operation = operation;
    node->left = NULL;
    node->right = NULL;
    node->n_childs = 0;
    return node;
}

// Función para insertar nodos en el AST según las reglas descritas
t_node *insert_redirection_node(t_node *root, t_token *token, t_list_token *prev, t_list_token *next) {
    t_node *new_node = create_ast_node(token);
    if (token->type == REDIR_R) {
        new_node->left = create_ast_node(prev->content);
        new_node->right = create_ast_node(next->content);
    } else if (token->type == REDIR_L) {
        new_node->left = create_ast_node(next->content);
        new_node->right = create_ast_node(prev->content);
    }
    new_node->n_childs = 2;
    return new_node;
}

t_node *ast_creator(t_list_token *start, t_list_token *end) {
    t_list_token *current = start;
    t_node *root = NULL;

    while (current && current != end) {
        if (current->content->type == REDIR_R || current->content->type == REDIR_L) {
            // Inserta el nodo de redirección con la estructura correcta
            root = insert_redirection_node(root, current->content, current->prev, current->next);
            
            // Avanza al siguiente nodo después del token de redirección
            if (current->next) {
                current = current->next->next; // Salta los nodos usados
            } else {
                current = current->next;
            }
        } else {
            // Caso general: construye el árbol como siempre
            if (!root) {
                root = create_ast_node(current->content);
            } else {
                t_node *new_node = create_ast_node(current->content);
                new_node->left = root;
                root = new_node;
            }
            current = current->next;
        }
    }
    return (root);
}
