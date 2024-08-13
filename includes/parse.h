/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/13 12:48:32 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token
{
    char        *content;
    int         type;
    int         priority;
        
}	t_token;

typedef struct s_node
{
    t_token     *operation;
    s_node      *left_content;
    s_node      *right_content;    
}	t_node;
