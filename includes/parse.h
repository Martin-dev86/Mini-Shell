/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/04 18:09:10 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <sys/wait.h>
# include <memory.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

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
	char				*content;
	int					len;
	size_t				variable_len;
	struct s_list_env	*next;
}	t_list_env;

typedef struct s_list_token
{
	t_token				*content;
	struct s_list_token	*next;
}	t_list_token;

// Exit function
void		    ft_exit(char *str, int code);

// Tokenizer
void			token_list_typer (t_list_token *token_list);
t_list_token	*token_read_filler(t_token token, t_list_token *head);

// DFA
int 			dfa_main (t_list_token *token_list);

// Expander
t_node 			*expand_tree(t_node *ast, t_list_env *env);

// AST creator
t_node 			*ast_creator(t_list_token *token_list);
t_node 			*final_tree (t_node *ast, t_list_env *env);

// Main parser
int 			main_parser(char **env, t_token *token);

