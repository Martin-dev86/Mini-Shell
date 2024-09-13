/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/09/13 18:40:30 by jeandrad         ###   ########.fr       */
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
	char 				**path;
}	t_list_env;

typedef struct s_list_token
{
	t_token				*content;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}	t_list_token;

// Helper functions
int ft_token_lst_size(t_list_token *lst);

// Exit function
void		    ft_exit(char *str, int code);

// Environment parser
char 			**get_path(char *path);

// Tokenizer
void			token_list_typer (t_list_token *token_list);
t_list_token	*token_read_filler(t_token token, t_list_token *head);

// DFA
int 			dfa_main (t_list_token *token_list);

// Expander
t_node 			*expand_tree(t_node *ast, t_list_env *env);
t_node 			*final_tree(t_node *ast, t_list_env *env);

// Pipe counter
int				count_pipe_tokens(t_node *root);

// AST creator
t_node			*ast_creator(t_list_token *start, t_list_token *end);
t_node 			*final_tree (t_node *ast, t_list_env *env);

// Main parser
t_node			*main_parser(char **env, t_token *token);

