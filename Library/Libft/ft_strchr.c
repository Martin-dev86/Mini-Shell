/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:59:21 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/30 14:13:54 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*found;

	while (*s)
	{
		if (*s == (char) c)
		{
			found = s;
			return ((char *) found);
		}
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return (NULL);
}
