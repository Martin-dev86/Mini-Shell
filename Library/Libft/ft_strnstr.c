/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:36:51 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/12 13:58:47 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*temp;
	char		*temp1;

	temp1 = (char *) needle;
	if (*needle == '\0')
		return ((char *) haystack);
	while (*haystack && len > 0)
	{
		temp = (char *) haystack;
		while (*haystack == *needle && 0 < len && *haystack)
		{
			len--;
			haystack++;
			needle++;
		}
		len = len + (haystack - temp);
		haystack = temp;
		if (*needle == '\0')
			return (temp);
		needle = temp1;
		len--;
		haystack++;
	}
	return (NULL);
}
