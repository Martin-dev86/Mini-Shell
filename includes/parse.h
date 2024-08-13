/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/13 20:58:42 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_type
{
    NONE,
    CMD,
    ARG,
    REDIR,
    PIPE,
    SEMICOLON,
    PARENTHESIS,
    BUILTIN,
    ENV,
    VARIABLE,
    EXPANSION,
    ASSIGNMENT,
    FILE,
    HEREDOC,
    ENDLINE
}	t_type;

typedef struct s_token
{
    char        *content;
    t_type      type;
    int         priority;
    char        *path;
}	t_token;

typedef struct s_node
{
    t_token     *operation;
    t_node      *left_content;
    t_node      *right_content;
    int         n_childs;
}	t_node;
>>>>>>> Parse
