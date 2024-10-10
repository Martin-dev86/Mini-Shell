/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:29:21 by jeandrad          #+#    #+#             */
/*   Updated: 2024/10/10 14:48:58 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>

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
}						t_type;

typedef struct s_token
{
	char				*read;
	t_type				type;
	int					priority;
	char				*path;
	int					len;
}						t_token;

typedef struct s_node
{
	t_token				*operation;
	struct s_node		*left;
	struct s_node		*right;
	int					n_childs;
	int					is_executing;
	int					temp_fd;
}						t_node;

typedef struct s_list_env
{
	char				*content;
	int					len;
	size_t				variable_len;
	struct s_list_env	*next;
	char				**path;
	char				**env;
}						t_list_env;

typedef struct s_list_token
{
	t_token				*content;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_list_token;

typedef struct s_list_shellenv
{
	t_list_env			*env;
}						t_list_shellenv;

// For the tokenizer
typedef struct s_token_counters
{
	int					i;
	int					j;
}						t_token_counters;

// For the expansion of the $ variables
typedef struct s_process_state
{
	bool				in_single_quote;
	bool				in_double_quote;
	size_t				res_index;
	size_t				i;
	size_t				len;
	size_t				alloc_size;
	char				*result;
	char				*exit_status;
	size_t				exit_len;
	size_t				var_start;
	char				var_name[256];
	char				*var_value;
	size_t				var_value_len;
}						t_processState;

//dollar_tools.c
char					*get_env_value(const char *key,
							t_list_shellenv *shellenv);
void					print_env(t_list_shellenv *shellenv);
void					handle_quotes(const char *input, t_processState *state);
void					expand_exit_status(t_son *son, t_processState *state);
void					extract_variable_name(const char *input, \
							t_processState *state);

// token_utils.c
void					set_prev_pointers(t_list_token *head);

// tokenizer_handle.c
char					*quote_catcher(char *str, int *i, int quote);
void					handle_quotes1(char **tokens, char *str,
							t_token_counters *counters, char quote);
void					handle_operator(char **tokens, char *op, int *j);
void					handle_token(char **tokens, char *str, int *i, int *j);
void					handle_special_operator(char **tokens, char *str,
							t_token_counters *counters);

// token_alloc.c
void					handle_redirection_operator(char **tokens, char *str,
							t_token_counters *counters);
void					handle_single_redirection_operator(char **tokens,
							char *str, t_token_counters *counters);
void					allocate_tokens(char **tokens, char *str);
void					count_quote_tokens(char *str, int *i, int *token_count);
void					skip_non_token_characters(char *str, int *i);

/// free_token_list.c
void					free_token_list(t_list_token *start);

// node_creator.c
t_node					*create_ast_node(t_token *operation);

// first_env.c
void					first_env(char **env);

// update_env_matrix.c
char					**create_env_matrix(t_list_env *env_list);

// count_quotes.c
int						count_quotes(const char *str);

// Helper functions
int						ft_token_lst_size(t_list_token *lst);

// Exit function
void					ft_exit(char *str, int code);

// Environment parser
char					**get_path(char *path);
char					*replace_variables(const char *input,
							t_list_shellenv *env, t_son *son);

// Tokenizer
void					token_list_typer(t_list_token *token_list);
t_list_token			*token_read_filler(t_token token, t_list_token *head);

// DFA
int						dfa_main(t_list_token *token_list);

// Expander
void					replace_env_vars(t_list_token *tokens,
							t_list_shellenv *env);
t_node					*expand_tree(t_node *ast, t_list_shellenv *env);
t_node					*final_tree(t_node *ast, t_list_shellenv *env);

// Pipe counter
int						count_pipe_tokens(t_node *root);

// AST creator
t_node					*ast_creator(t_list_token *start, t_list_token *end);
t_node					*final_tree(t_node *ast, t_list_shellenv *env);

// Main parser
t_node					*main_parser(t_list_shellenv *env, t_token *token,
							t_son *son);
