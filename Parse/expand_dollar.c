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
    while (shellenv) {
        if (strncmp(shellenv->env->content, key, key_len) == 0 && shellenv->env->content[key_len] == '=') {
			return (shellenv->env->content + key_len + 1); // Skip past "key="
        }
        shellenv->env = shellenv->env->next;
    }
    return ("");
}

char *replace_variables(const char *input, t_list_shellenv *shellenv, t_son *son) 
{
	bool in_single_quote = false;
	bool in_double_quote = false;
	size_t len = strlen(input);
	char *result = malloc(len * 50); // Allocate more space for potential expansions
	if (!result) return NULL;
	size_t res_index = 0;

	for (size_t i = 0; i < len; i++)
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
			if (exit_status) {
				strcpy(&result[res_index], exit_status);
				res_index += strlen(exit_status);
				free(exit_status); // Libera la memoria después de usarla
			}
			i++; // Salta el '?'
		}
		else if (input[i] == '$' && !in_single_quote)
		{
			size_t var_start = ++i;
			while (i < len && (isalnum(input[i]) || input[i] == '_')) i++;
			char var_name[256];
			strncpy(var_name, &input[var_start], i - var_start);
			var_name[i - var_start] = '\0';
			printf("\n\nHOLAAAA\n\n");
			char *var_value = get_env_value(var_name, shellenv);
			printf("\n\nADIOS\n\n");
			strcpy(&result[res_index], var_value);
			res_index += strlen(var_value);
			i--; // Adjust for the increment in the loop
		}
		else
		{
			result[res_index++] = input[i];
		}
	}
	result[res_index] = '\0';
	if (in_single_quote || in_double_quote)
	{
		free(result);
		return (NULL); // Unmatched quotes
	}
    return result;
}
