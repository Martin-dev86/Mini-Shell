#include "libft.h"

void	ft_realloc(void **s, size_t old_size, size_t new_size)
{
	size_t			i;
	unsigned char	*m;

	m = *(unsigned char **)s;
	if (!(*(unsigned char **)s =
				(unsigned char *)malloc(sizeof(unsigned char) * new_size)))
		return ;
	i = 0;
	while (i < old_size)
	{
		(*(unsigned char **)s)[i] = m[i];
		i++;
	}
	free(m);
}
