/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:09:46 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/09 16:20:04 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:15:01 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/09 16:15:10 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, int n)
{
	int		copy_n;
	char	*new_ptr;

	copy_n = 0;
	new_ptr = NULL;
	if (n <= 0)
		return (NULL);
	new_ptr = malloc(n * sizeof(char));
	if (!new_ptr)
		return (free(ptr), NULL);
	if (ptr)
	{
		copy_n = ft_strlen(ptr);
		if (copy_n > n - 1)
			copy_n = n - 1;
		ft_memcpy(new_ptr, ptr, copy_n);
		free(ptr);
	}
	new_ptr[copy_n] = '\0';
	return (new_ptr);
}
