/* ************************************************************************** */
/*												      */
/*									    :::      ::::::::   */
/*   expand_dollar.c									:+:      :+:    :+:   */
/*									+:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*						        +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:40:30 by jeandrad          #+#    #+#			*/
/*   Updated: 2024/10/04 18:48:43 by cagarci2         ###   ########.fr       */
/*												      */
/* ************************************************************************** */

/*												      */
/*									    :::      ::::::::   */
/*   expand_dollar.c									:+:      :+:    :+:   */
/*									+:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*						        +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:40:30 by jeandrad          #+#    #+#			*/
/*   Updated: 2024/09/24 16:51:08 by jeandrad         ###   ########.fr       */
/*												      */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(const char *key, t_list_shellenv *shellenv)
{
    size_t key_len = strlen(key);
	t_list_env *current = shellenv->env;

    while (current)
	{
        if (strncmp(current->content, key, key_len) == 0 && current->content[key_len] == '=')
			return (current->content + key_len + 1); // Skip past "key="
        current = current->next;
    }
    return (NULL);
}
void print_env(t_list_shellenv *shellenv) {
    t_list_env *current = shellenv->env; // Comienza desde el inicio de la lista

    printf("Variables de entorno:\n");
    while (current) {
        printf("%s\n", current->content); // Imprime cada variable de entorno
        current = current->next; // Mueve al siguiente nodo
    }
}

char *replace_variables(const char *input, t_list_shellenv *shellenv, t_son *son) 
{
    bool in_single_quote = false;
    bool in_double_quote = false;
    size_t len = strlen(input);
    size_t alloc_size = len + 1;  // Asignamos memoria inicialmente para la longitud del input + '\0'
    char *result = malloc(alloc_size); // Inicialmente asignamos lo que cabe en el input
    if (!result) return NULL;
    
    size_t res_index = 0;
    size_t i = 0;

    while (i < len)
    {
        if (input[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            result[res_index++] = input[i];
        }
        else if (input[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            result[res_index++] = input[i];
        }
        else if (input[i] == '$' && input[i + 1] == '?')
        {
            char *exit_status = ft_itoa(son->code); // Convierte el código de salida a cadena
            if (exit_status)
            {
                size_t exit_len = strlen(exit_status);
                
                // Verificamos si necesitamos más memoria
                if (res_index + exit_len >= alloc_size)
                {
                    alloc_size += exit_len + 1;
                    result = realloc(result, alloc_size);  // Redimensionamos la memoria
                    if (!result) return NULL;  // En caso de fallo
                }

                strcpy(&result[res_index], exit_status);
                res_index += exit_len;
                free(exit_status);
            }
            i++; // Saltamos el '?'
        }
        else if (input[i] == '$' && !in_single_quote)
        {
            size_t var_start = ++i;
            while (i < len && (isalnum(input[i]) || input[i] == '_')) i++;

            char var_name[256];
            ft_strlcpy(var_name, &input[var_start], i - var_start + 1);

            char *var_value = get_env_value(var_name, shellenv);
            size_t var_value_len = var_value ? strlen(var_value) : 0;

            if (var_value)
            {
                // Verificamos si necesitamos más memoria
                if (res_index + var_value_len >= alloc_size)
                {
                    alloc_size += var_value_len + 1;
                    result = realloc(result, alloc_size);  // Redimensionamos la memoria
                    if (!result) return NULL;  // En caso de fallo
                }

                strcpy(&result[res_index], var_value);
                res_index += var_value_len;
            }
            i--;  // Ajustamos por el incremento del ciclo
        }
        else
        {
            if (res_index + 1 >= alloc_size)
            {
                alloc_size += 1;
                result = realloc(result, alloc_size);  // Redimensionamos la memoria
                if (!result) return NULL;  // En caso de fallo
            }

            result[res_index++] = input[i];
        }

        i++;
    }

    result[res_index] = '\0';

    // Verificamos si alguna comilla quedó sin cerrar
    if (in_single_quote || in_double_quote)
    {
        free(result);
        return NULL; // Comillas no emparejadas
    }

    return result;
}