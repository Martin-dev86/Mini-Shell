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

NAME = libft.a

SOURCES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		 ft_strlen.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_memcmp.c \
		 ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strchr.c ft_strrchr.c \
		 ft_strnstr.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		 ft_memchr.c ft_calloc.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c \
		 ft_putlendl_fd.c ft_putnbr_fd.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		 ft_itoa.c ft_striteri.c ft_strmapi.c ft_split.c \
		 ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstadd_front.c \
		 ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strcmp.c

OBJ = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

all: 	$(NAME) 

$(NAME):	$(OBJ) 
			@ ar rcs $(NAME) $(OBJ)
			@echo "\n${YELLOW} ► $(GREEN)$(BOLD)Created $(NAME) correctly$(DEF_COLOR)\n"

%.o: %.c Makefile
	@echo "${YELLOW} • $(CYAN)COMPILE ${RED}→ $(DARK_GRAY)$< ${GREEN}✓$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "\n${YELLOW} ¤ $(ORANGE)objects cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

fclean: clean	
	@$(RM) $(NAME)
	@echo "${YELLOW} ¤ $(ORANGE)executables cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

re: fclean all 

.PHONY: all clean fclean re libft