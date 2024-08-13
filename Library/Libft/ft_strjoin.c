/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:29:37 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/19 13:27:35 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	int		totalen;
	char	*str;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	totalen = lens1 + lens2;
	str = malloc(sizeof(char) * totalen +1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, lens1);
	ft_memcpy(str + lens1, s2, lens2 +1);
	return (str);
}
