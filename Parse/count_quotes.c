/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:42:36 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 14:52:09 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_quotes(const char *str)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			d_quote++;
		if (str[i] == 39)
			s_quote++;
		i++;
	}
	if (d_quote == 0 || s_quote == 0)
		return (0);
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
		return (-1);
	return (0);
}
