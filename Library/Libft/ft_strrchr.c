/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:10:57 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/19 13:51:13 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	int			i;

	i = ft_strlen((const char *) s);
	while (*s)
		s++;
	while (i >= 0)
	{
		if (*s == (char) c)
		{
			found = s;
			return ((char *) found);
		}
		i--;
		s--;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return (NULL);
}
