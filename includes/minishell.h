/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:38:01 by cagarci2          #+#    #+#             */
/*   Updated: 2024/09/16 22:26:25 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/wait.h>
# include <memory.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "execute.h"
# include "parse.h"

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\033[37m"
# define GREYM		"\x1B[38;5;245m"
# define GREYM2		"\x1B[38;5;250m"
# define BOLD		"\033[1m"
# define RESET		"\x1b[0m"
# define CLEAR		"\033[2J"

int			execute(t_son *son, t_list_env *env, t_node *node);
int			execute_builtins(t_son *son, t_list_env *env, t_node *node);
char		*get_pwd(void);
int			mini_pwd(t_son *son);
int			mini_echo(t_token *token);
int			mini_redirect(t_token *token, t_son *son);
int			mini_env(t_list_env *env);
int			mini_unset(t_list_env *env, t_token *token);
int			mini_export(t_list_env *env, t_token *token);
int			mini_cd(t_node *node, t_list_env *env);
void		mini_sort(t_list_env *sorted_current, t_list_env *current);
void		mini_lstadd_back(t_list_env **lst, t_list_env *new);
int			mini_strlen(const char *c);
int         mini_pipe(t_son *son, t_node *node, t_list_env *env);
int         mini_cmd(t_list_env *env, t_son *son, t_node *node);
t_list_env	*mini_lstnew(void *content);
t_list_env	*mini_lstlast(t_list_env *lst);
t_list_env	*env_parse(char **env);
void		print_ast(t_node *root);
#endif