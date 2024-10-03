#include "libft.h"

char *ft_strstr(const char *haystack, const char *needle)
{
    size_t needle_len;

    if (*needle == '\0')
        return (char *)haystack;

    needle_len = ft_strlen(needle);
    while (*haystack)
    {
        if (ft_strncmp(haystack, needle, needle_len) == 0)
            return (char *)haystack;
        haystack++;
    }
    return NULL;
}