/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:52 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/09 10:48:06 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_token_lst_size(t_list_token *lst)
{
    int size = 0;
    while (lst)
    {
        size++;
        lst = lst->next;
    }
    return (size);
}