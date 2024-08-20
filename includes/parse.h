/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/20 12:45:24 by cagarci2         ###   ########.fr       */
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
	APPEND,
}	t_type;

typedef struct s_token
{
	char		*content;
	t_type		type;
	int			priority;
	char		*path;
}	t_token;

typedef struct s_node
{
	t_token				*operation;
	struct s_node		*left_content;
	struct s_node		*right_content;
	int					n_childs;
}	t_node;

//List for the env variables
typedef struct s_list
{
	int				content;
	struct s_list	*next;
}					t_list;

char	**token_maker(t_token *token, char **env);