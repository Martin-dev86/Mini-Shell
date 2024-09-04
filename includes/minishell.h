/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/04 11:11:14 by jeandrad         ###   ########.fr       */
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

char		*get_pwd(void);
int			mini_pwd(t_son *son, t_token *token);
int			execute(t_token *token, t_son *son, t_list_env *env);
int			execute_builtins(t_token *token, t_son *son, t_list_env *env);
void		print_ast(t_node *root);
int			mini_echo(t_son *son, t_token *token);
int			mini_redirect(t_token *token, t_son *son);
int			mini_env(t_list_env *env);
int			mini_unset(t_list_env *env, t_token *token);
int			mini_export(t_list_env *env, t_token *token);
t_list_env	*env_parse(char **env);
int			mini_cd(t_token *token, t_list_env *env);
void		mini_sort(t_list_env *sorted_current, t_list_env *current);
t_list_env	*mini_lstnew(void *content);
t_list_env	*mini_lstlast(t_list_env *lst);
void		mini_lstadd_back(t_list_env **lst, t_list_env *new);
int			mini_strlen(const char *c);
#endif