# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:45:34 by cagarci2          #+#    #+#              #
#    Updated: 2024/03/22 12:45:34 by cagarci2         ###   ########.fr        #
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

SRC_DIR = ./

LIBFT	= Library/Libft
READLINE = -lreadline -ltinfo

SRC_FILES =		$(wildcard $(SRC_DIR)/*.c)
SRC = 			$(addprefix $(SRC_DIR)/, $(SRC_FILES))
LIBS	= $(LIBFT)/libft.a -ldl -lglfw -pthread -lm  -L"/Users/$(USER)/.brew/opt/glfw/lib/"
OBJ_SRC		=	$(SRC_FILES:.c=.o)

HEADER_DIR	=	includes
HEADER_SRCS	=	minishell.h \
HEADER		=	$(addprefix $(HEADER_DIR)/, $(HEADER_SRCS))

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -Iincludes -I$(LIBFT)

RM = rm -f

all:	libft $(NAME) 

libft:
	@make --no-print-directory -C $(LIBFT)

%.o: %.c Makefile
	@echo "${YELLOW} • $(CYAN)COMPILE ${RED}→ $(DARK_GRAY)$< ${WHITE}✓$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -L./$(FT_PRINTF) -c $< -o $@

$(NAME):	$(OBJ_SRC) 
			@$(CC) $(OBJ_SRC) $(LIBS) -o $(NAME) $(READLINE)
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