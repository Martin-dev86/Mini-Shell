/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:09:46 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/09 16:12:20 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_realloc(void **s, size_t old_size, size_t new_size)
{
	size_t			i;
	unsigned char	*m;

	m = *(unsigned char **)s;
	if (!*(unsigned char **)s)
	{
		(*(unsigned char **)s = \
			(unsigned char *)malloc(sizeof(unsigned char) * new_size));
		return ;
	}
	i = 0;
	while (i < old_size)
	{
		(*(unsigned char **)s)[i] = m[i];
		i++;
	}
	free(m);
}
