#include "minishell.h"

char *find_env_value(t_list_env *env_list, const char *key) 
{
    while (env_list) 
    {
        // Compare only the variable name
        if (strncmp(env_list->content, key, env_list->variable_len) == 0 &&
            env_list->content[env_list->variable_len] == '=')
            return env_list->content + env_list->variable_len + 1; // Return the value after the =
        env_list = env_list->next;
    }
    return NULL;
}

// Good function to replace variables in a string
char *replace_variables(const char *input, t_list_env *env_list)
{
    int in_single_quote = 0;
    int in_double_quote = 0;
    //char *result = malloc(strlen(input) * 2 + 1);
    char *result = ft_calloc(strlen(input) * 2 + 1, sizeof(char));
    char *res_ptr = result;

    while (*input) {
        if (*input == '\'')
            in_single_quote = !in_single_quote; // Quote state
        else if (*input == '\"')
            in_double_quote = !in_double_quote; //  Dquote state
        else if (*input == '$' && (in_double_quote || !in_single_quote)) 
        {
            // Find the end of the variable name
            const char *start = input + 1;
            while (*start && (*start == '_' || isalnum(*start))) 
                start++;
            int var_len = start - (input + 1);
            char *key = strndup(input + 1, var_len); // Get the variable name
            char *value = find_env_value(env_list, key); // get the value of the variable

            if (value) 
            {
                strcpy(res_ptr, value); // copy the value to the result
                res_ptr += strlen(value);
            }
            free(key);
            input = start - 1;
        } 
        else 
        {
            *res_ptr = *input; // copy the character to the result
            res_ptr++;
        }
        input++;
    }
    *res_ptr = '\0';
    return (result);
}

