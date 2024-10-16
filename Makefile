# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:45:34 by cagarci2          #+#    #+#              #
#    Updated: 2024/10/11 08:40:17 by jeandrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

NAME = minishell

SRC_DIR = ./ ./Execute ./Parse
LIBFT	= Library/Libft
READLINE = -lreadline -ltinfo

LIBS	= $(LIBFT)/libft.a
SRC_FILES =		$(shell find $(SRC_DIR) -name '*.c')
OBJ_SRC		=	Parse/token_utils.o Parse/tokenizer_handle.o Parse/token_alloc.o Parse/free_token_list.o\
				Parse/node_creator.o Parse/dollar_tools.o Parse/first_env.o Parse/update_env_matrix.o\
				Execute/built-ins/mini_exit.o Execute/ft_free.o Execute/ft_free_token.o Parse/count_quotes.o\
				Execute/redirect.o Execute/execute.o Parse/ft_exit.o Parse/token_lst_size.o Parse/get_path.o Parse/env_parse.o\
				Parse/token_typer.o Parse/count_pipe.o Parse/tokenizer.o Parse/expand_dollar.o\
				Execute/pipe.o Execute/cmd.o Parse/ft_heredoc.o banner.o Execute/ft_free_env.o\
				Parse/parse_main.o Parse/dfa.o Parse/list.o Parse/ast_creator.o Parse/expander.o Execute/signal.o \
				Execute/built-ins/mini_pwd.o Execute/built-ins/mini_export_help.o Execute/built-ins/mini_unset.o  \
				Execute/built-ins/mini_export.o \
				Execute/built-ins/mini_env.o Execute/built-ins/mini_echo.o Execute/built-ins/mini_cd.o  main.o Print_tree.o

HEADER_DIR	=	includes
HEADER_SRCS	=	minishell.h \
HEADER		=	$(addprefix $(HEADER_DIR)/, $(HEADER_SRCS))

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -I$(HEADER_DIR) -I$(LIBFT) 
RM = rm -f

all:	libft $(NAME) 

libft:
	@make --no-print-directory -C $(LIBFT)
	
%.o: %.c
	@echo "${YELLOW} • $(CYAN)COMPILE ${RED}→ $(DARK_GRAY)$< ${WHITE}✓$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME):	$(OBJ_SRC) 
			@$(CC) $(OBJ_SRC) -o $(NAME) $(READLINE) $(LIBS)
			@echo "\n${YELLOW} ► $(GREEN)$(BOLD)Created $(NAME) correctly$(DEF_COLOR)\n"

clean:
	@make clean -C $(LIBFT) > /dev/null 2>&1
	@$(RM) $(OBJ_SRC) 
	@echo "\n${YELLOW} ¤ $(ORANGE)objects cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

fclean: clean	
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)/libft.a
	@echo "${YELLOW} ¤ $(ORANGE)executables cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

re: fclean all 

.PHONY: all clean fclean re libft