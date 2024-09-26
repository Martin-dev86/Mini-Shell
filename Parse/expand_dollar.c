/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:40:30 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/26 12:28:30 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *key, t_list_env *env_list)
{
	size_t	key_len;

	key_len = strlen(key);
	while (env_list)
	{
		if (strncmp(env_list->content, key, key_len) == 0
			&& env_list->content[key_len] == '=')
			return (env_list->content + key_len + 1); // Skip past "key="
		env_list = env_list->next;
	}
	return ("");
}

char	*replace_variables(const char *input, t_list_env *env_list)
{
	bool	in_single_quote;
	bool	in_double_quote;
	size_t	len;
	size_t	res_index;
	size_t	var_start;
	char	var_name[256];
	char	*var_value;

	in_single_quote = false;
	in_double_quote = false;
	len = strlen(input);
	char *result = malloc(len * 50);
		// Allocate more space for potential expansions
	if (!result)
		return (NULL);
	res_index = 0;
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
		else if (input[i] == '$' && !in_single_quote)
		{
			var_start = ++i;
			while (i < len && (isalnum(input[i]) || input[i] == '_'))
				i++;
			strncpy(var_name, &input[var_start], i - var_start);
			var_name[i - var_start] = '\0';
			var_value = get_env_value(var_name, env_list);
			strcpy(&result[res_index], var_value);
			res_index += strlen(var_value);
			i--; // Adjust for the increment in the loop
		}
		else
			result[res_index++] = input[i];
	}
	result[res_index] = '\0';
	if (in_single_quote || in_double_quote)
	{
		free(result);
		return (NULL); // Unmatched quotes
	}
	return (result);
}

// Example usage
// int main() {
//     t_list_env env1 = {"USER=jeandrad", 12, 4, NULL, NULL, NULL};
//     t_list_env env2 = {"HOME=/home/jeandrad", 18, 4, &env1, NULL, NULL};
//     t_list_env env3 = {"SHELL=/bin/bash", 15, 5, &env2, NULL, NULL};

//     char *input = "Hello $USER,
//	your home is \"$HOME\" and shell is '$SHELL'";
//     char *output = replace_variables(input, &env3);

//     if (output) {
//         printf("%s\n", output);
//         free(output);
//     } else {
//         printf("Error: Unmatched quotes\n");
//     }

//     return (0);
// }