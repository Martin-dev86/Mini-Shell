/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/08/23 12:13:02 by cagarci2         ###   ########.fr       */
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
	char		*read;
	char		**argument;
	t_type		type;
	int			priority;
	char		*path;
	int			len;
}	t_token;

typedef struct s_node
{
	t_token				*operation;
	struct s_node		*left;
	struct s_node		*right;
	int					n_childs;
}	t_node;

typedef struct s_list_env
{
	char			*content;
	struct s_list	*next;
}	t_list_env;

char	**token_maker(t_token *token, char **env);
void	token_typer(t_token *token);