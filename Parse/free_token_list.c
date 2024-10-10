/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:10:36 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 10:30:56 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

// Function to free the entire token list starting from 'start'
#include "minishell.h"

// Function to free the entire token list starting from 'start'
void	free_token_list(t_list_token *start)
{
	t_list_token	*current;
	t_list_token	*next;

	current = start;

	// Si 'start' es NULL, no hay nada que liberar
	if (start == NULL)
		return;

	// Recorre la lista desde 'start' hasta el final
	while (current != NULL)
	{
		next = current->next; // Guarda el siguiente nodo

		// Imprime el token actual y los punteros para diagnóstico
		if (current->content)
		{
			printf("Freeing token: %s\n", current->content->read);
			// Libera el campo 'read' si está asignado
			if (current->content->read)
			{
				free(current->content->read);
				current->content->read = NULL; // Evita accesos a memoria ya liberada
			}
			
			// Libera el campo 'path' si está asignado
			if (current->content->path)
			{
				free(current->content->path);
				current->content->path = NULL; // Evita accesos a memoria ya liberada
			}

			// Finalmente, libera la estructura del token
			free(current->content);
			current->content = NULL; // Evita accesos a memoria ya liberada
		}

		// Libera el nodo de la lista de tokens
		free(current);

		// Para evitar problemas con listas cíclicas, asegúrate de que el siguiente nodo sea válido
		current = next;  // Avanza al siguiente nodo
	}

	// Asegúrate de que la lista ha terminado correctamente
	printf("Finished freeing tokens.\n");
}
