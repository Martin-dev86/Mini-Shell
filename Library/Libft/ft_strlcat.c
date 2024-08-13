/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:35:00 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/30 12:03:37 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;
	size_t	remaining_space;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	total_len = dst_len + src_len;
	remaining_space = dstsize - dst_len - 1;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	while (*dst)
		dst++;
	while (*src && remaining_space > 0)
	{
		*dst = *src;
		dst++;
		src++;
		remaining_space--;
	}
	*dst = '\0';
	return (total_len);
}
