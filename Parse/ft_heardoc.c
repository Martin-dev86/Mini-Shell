#include "minishell.h"

void ft_heardoc(const char *delimiter)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 
            && line[ft_strlen(delimiter)] == '\n')
        {
            break;
        }
        // Process the line (e.g., store it, print it, etc.)
        printf("Read: %s", line);
    }

    free(line);
}

void process_heardoc(char *str)
{
    char *heardoc_pos;
    while ((heardoc_pos = ft_strstr(str, "<<")) != NULL)
    {
        // Move past the "<<"
        heardoc_pos += 2;

        // Skip any whitespace
        while (*heardoc_pos == ' ')
        {
            heardoc_pos++;
        }

        // Find the end of the delimiter
        char *delimiter_end = heardoc_pos;
        while (*delimiter_end != ' ' && *delimiter_end != '\0')
        {
            delimiter_end++;
        }

        // Extract the delimiter
        size_t delimiter_len = delimiter_end - heardoc_pos;
        char *delimiter = (char *)malloc(delimiter_len + 1);
        ft_strncpy(delimiter, heardoc_pos, delimiter_len);
        delimiter[delimiter_len] = '\0';

        // Execute the here-doc function
        ft_heardoc(delimiter);

        // Remove the "<< delimiter" part from the command string
        ft_memmove(heardoc_pos - 2, delimiter_end, ft_strlen(delimiter_end) + 1);

        // Free the allocated memory for the delimiter
        free(delimiter);
    }
}
