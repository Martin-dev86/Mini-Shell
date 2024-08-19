/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/19 19:53:33 by jeandrad         ###   ########.fr       */
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
    FILE_PATH,
    HEREDOC,
    ENDLINE,
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
    t_token             *operation;
    struct s_node      *left_content;
    struct s_node      *right_content;
    int                 n_childs;
}	t_node;

//List for the env variables
typedef struct s_list
{
	int				content;
    
	struct s_list	*next;
}					t_list;

char **token_maker(t_token *token, char **env);