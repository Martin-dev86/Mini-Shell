/* ************************************************************************** */
/*																		    */
/*														:::      ::::::::   */
/*   minishell.h										:+:      :+:    :+:   */
/*												    +:+ +:+		 +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/12 18:38:01 by cagarci2		  #+#    #+#		     */
/*   Updated: 2024/10/04 00:20:18 by cagarci2		 ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
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

extern int	g_prompt_active;

void		ft_free_token(t_token *token);
void		ft_free_env(t_list_env *env);
void		free_token_list_without_content(t_list_token *start);
int			execute(t_son *son, t_list_shellenv *shellenv, t_node *node);
int			execute_builtins(t_son *son, t_list_shellenv *shellenv, \
			t_node *node);
char		*get_pwd(void);
void		mini_exit(t_node *node, t_list_shellenv *shellenv, \
			t_son *son, int status);
int			mini_pwd(t_son *son);
int			mini_echo(t_node *node, t_son *son);
int			mini_redirect(t_node *node, t_son *son, t_list_shellenv *shellenv);
int			mini_env(t_list_shellenv *shellenv);
t_list_env	*find_last_match(t_list_env *env, size_t len, \
				char *final_unset_var, t_list_env **prev_last_match);
void		found_equal(t_list_shellenv *shellenv, t_node *node);
void		final_unset(t_list_shellenv *shellenv,
				size_t len, char *final_unset_var);
int			mini_unset(t_list_shellenv *shellenv, t_node *node);
int			mini_export(t_list_shellenv *shellenv, t_node *node);
int			mini_cd(t_node *node, t_list_shellenv *shellenv);
void		mini_sort(t_list_env *sorted_current, t_list_env *current);
void		mini_lstadd_back(t_list_env **lst, t_list_env *new);
int			mini_strlen(const char *c);
int			mini_pipe(t_son *son, t_node *node, t_list_shellenv *shellenv);
int			mini_cmd(t_list_shellenv *shellenv, t_son *son, t_node *node);
t_list_env	*mini_lstnew(void *content);
t_list_env	*mini_lstlast(t_list_env *lst);
t_list_env	*env_parse(char **env);
void		print_ast(t_node *root);
void		sigquit_handler(int signo);
void		sigint_handler(int signo);
void		setup_signals(void);
void		handle_heredoc(t_node *node, t_son *son);
void		ft_baby_yoda_banner(void);
void		del_node(t_list_env *env);
int			mini_strlen(const char *c);
void		ft_free(t_list_shellenv *shellenv, t_node *node, \
			t_list_token *token, t_son *son);
void		update_path(t_list_shellenv *shellenv);

#endif