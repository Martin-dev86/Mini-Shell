/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/06 23:40:09 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <memory.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum e_type
{
	NONE,
	CMD,
	ARG,
	REDIR_R,
	REDIR_L,
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
	int					is_executing;
}	t_node;

typedef struct s_list_env
{
	char				*content;
	int					len;
	size_t				variable_len;
	struct s_list_env	*next;
	char				**path;
	char				**env;
}	t_list_env;

typedef struct s_list_token
{
	t_token				*content;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}	t_list_token;

typedef struct s_list_shellenv
{
	t_list_env	*env;
}	t_list_shellenv;
// Helper functions
int				ft_token_lst_size(t_list_token *lst);

// Exit function
void			ft_exit(char *str, int code);

// Environment parser
char			**get_path(char *path);
char	*replace_variables(const char *input, t_list_shellenv *env, t_son *son);

// Tokenizer
void			token_list_typer(t_list_token *token_list);
t_list_token	*token_read_filler(t_token token, t_list_token *head);

// DFA
int				dfa_main(t_list_token *token_list);

// Expander
void			replace_env_vars(t_list_token *tokens, t_list_shellenv *env);
t_node			*expand_tree(t_node *ast, t_list_shellenv *env);
t_node			*final_tree(t_node *ast, t_list_shellenv *env);

// Pipe counter
int				count_pipe_tokens(t_node *root);

// AST creator
t_node			*ast_creator(t_list_token *start, t_list_token *end);
t_node			*final_tree(t_node *ast, t_list_shellenv *env);

// Main parser
t_node			*main_parser(t_list_shellenv *env, t_token *token, t_son *son);
