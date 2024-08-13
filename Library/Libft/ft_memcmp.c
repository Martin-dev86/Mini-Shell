/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:25:18 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/16 15:56:33 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (*p_s1 != *p_s2)
			return (*p_s1 - (*p_s2));
		p_s1++;
		p_s2++;
		n--;
	}
	return (*p_s1 - *p_s2);
}
