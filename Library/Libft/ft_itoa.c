/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:50:41 by cagarci2          #+#    #+#             */
/*   Updated: 2023/10/24 13:15:03 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len_num(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i++;
		n = n / 10;
	}
	if (n <= 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*print_char(unsigned int num, char *str, int len)
{
	char			*convert;

	convert = str;
	while (len > 0)
	{
		convert[len - 1] = '0' + num % 10;
		num /= 10;
		len--;
	}
	return (convert);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	num;

	num = n;
	len = len_num(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	str[len] = '\0';
	if (n < 0)
		num = -num;
	str = print_char(num, str, len);
	if (n < 0)
		str[0] = '-';
	return (str);
}
