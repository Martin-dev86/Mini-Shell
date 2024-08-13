/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:31:29 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/17 11:36:01 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s1);
	p = malloc (sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, len + 1);
	return (p);
}
