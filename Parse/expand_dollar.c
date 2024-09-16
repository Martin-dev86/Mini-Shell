#include "minishell.h"

// Function to obtain the value of a env variable in the env_list
char *get_env_value(t_list_env *env_list, const char *var)
{
    t_list_env *current = env_list;
    size_t var_len = strlen(var);

    while (current)
    {
        // Search if the variabe starts with the name and =
        if (strncmp(current->content, var, var_len) == 0 && current->content[var_len] == '=')
        {
            // returns the value after = 
            return current->content + var_len + 1;
        }
        current = current->next;
    }
    return NULL; // if there are not any values with that name in the list
}

// Function to realize the sustitution of env variables in the token_list 
void replace_env_vars(t_list_token *tokens, t_list_env *env_list)
{
    t_list_token *current = tokens;

    while (current)
    {
        char *read = current->content->read;

        // Verify if the token has an $
        char *dollar_sign = strchr(read, '$');
        if (dollar_sign)
        {
            // Extracts the name of the varible after the $
            int var_len = 0;
            char *var_start = dollar_sign + 1;

            while (var_start[var_len] && var_start[var_len] != ' ' && var_start[var_len] != '\0')
                var_len++;

            char *var_name = strndup(var_start, var_len);

            // Search the value of the variable in the env_list
            char *env_value = get_env_value(env_list, var_name);
            free(var_name);

            if (env_value)
            {
                // Does the substitution
                size_t new_len = strlen(read) - (var_len + 1) + strlen(env_value); // New length
                char *new_token = malloc(new_len + 1);

                if (new_token)
                {
                    // Copies the part before the $
                    size_t prefix_len = dollar_sign - read;
                    strncpy(new_token, read, prefix_len);

                    // Add the env variable value
                    strcpy(new_token + prefix_len, env_value);

                    // Add the part after the variable
                    strcpy(new_token + prefix_len + strlen(env_value), var_start + var_len);

                    // replaces the token value before $ expansion with the new value after $ expansion
                    free(current->content->read);
                    current->content->read = new_token;
                }
            }
        }
        current = current->next;
    }
}
