/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:24:34 by cagarci2          #+#    #+#             */
/*   Updated: 2024/07/16 12:56:42 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

size_t	count_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*search_char(char *str, int c)
{
	char	*aux;

	if (!str)
		return (NULL);
	aux = str;
	while (*aux != '\0')
	{
		if (*aux == (char) c)
			return (aux);
		aux++;
	}
	if ((char) c == '\0')
		return (str);
	return (NULL);
}

int	search_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*join_str(char *str1, char *str2)
{
	size_t				total_len;
	char				*full_str;
	int					i;
	int					j;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (ft_free(&str1), NULL);
	total_len = (count_len(str1) + count_len(str2));
	full_str = (char *)malloc(sizeof(char) * total_len + 1);
	if (!full_str)
		return (NULL);
	while (str1 && str1[i] != '\0')
		full_str[j++] = str1[i++];
	i = 0;
	while (str2 && str2[i] != '\0')
		full_str[j++] = str2[i++];
	full_str[j] = '\0';
	ft_free(&str1);
	return (full_str);
}
