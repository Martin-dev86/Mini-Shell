/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:35 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/10 18:08:41 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	delimiter(char const *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	next_word(char const *str, char c, int i)
{
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

static int	count_words(const char *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			words++;
			i = delimiter(str, c, i);
		}
		else
			i++;
	}
	return (words);
}

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(const char *str, char c)
{
	char	**result;
	int		wrds;
	int		i;
	int		j;

	wrds = count_words(str, c);
	result = (char **) malloc(sizeof(char *) * (wrds + 1));
	if (!str || !result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < wrds)
	{
		i = next_word(str, c, i);
		result[j] = ft_substr(str, i, delimiter(str, c, i) - i);
		if (!result[j])
		{
			free_split(result);
			return (NULL);
		}
		i = delimiter(str, c, i);
		j++;
	}
	result[j] = NULL;
	return (result);
}
