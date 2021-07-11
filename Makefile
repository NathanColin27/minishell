# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2021/01/21 17:15:52 by adorigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = srcs

SRC_NAME =	minishell.c						\
			\
			built-in/bltin_echo.c			\
			built-in/bltin_exit.c			\
			built-in/bltin_pwd.c			\
			built-in/bltin_env.c			\
			built-in/bltin_unset.c			\
			built-in/bltin_export.c			\
			built-in/bltin_cd.c 			\
			\
			cmd/get_static.c				\
			cmd/exec_cmd.c					\
			cmd/exec_external.c				\
			\
			environment/env.c				\
			environment/env2.c				\
			environment/dollar.c			\
			environment/shlvl.c				\
			\
			errors/errors.c					\
			errors/errors2.c				\
			errors/errors3.c				\
			errors/errors4.c				\
			errors/errors5.c				\
			\
			parsing/brackets.c				\
			parsing/cmd_parser_1.c			\
			parsing/cmd_parser_2.c			\
			parsing/lexing.c				\
			parsing/line_handle.c			\
			\
			redirections/cmd_add_rdir.c		\
			redirections/redirections.c		\
			redirections/pipe.c				\
			\
			utils/exit.c					\
			utils/files.c					\
			utils/free.c					\
			utils/ft_split_empty.c			\
			utils/ft_split_skip_quotes.c	\
			utils/utils.c					\
			utils/utils2.c					\
			utils/utils3.c					\
			utils/utils4.c					\
			utils/utils5.c

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I include -I libft/includes 
LDFLAGS = -L libft #-fsanitize=address
LDLIBS = -lft 

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:%.c=%.o)

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	TICK = \342\234\224
	RE = \342\231\272
	TRASH = \360\237\227\221
else
	TICK = \xE2\x9C\x94
	RE = \xE2\x99\xBA
	TRASH = \xF0\x9F\x97\x91
endif

default:
	@make -s all

all: libft $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@$(call update)
	@echo "\033[32;1m\rMinishell by adorigo & ncolin compiled ${TICK}          \033[0m"

libft:
	@make -s -C libft

libft_bonus:
	@make -s -C libft bonus
	
.SILENT:clean

clean:
	@make -s -C libft clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[32;1m\rDirectory cleaned ${TRASH}          \033[0m"

clean_libft:
	@make -s -C libft clean

clean_minishell:
	@rm -rf $(OBJ)

fclean_libft:
	@make -s -C libft fclean

fclean_minishell:
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	

fclean: fclean_minishell fclean_libft
	@echo "\033[32;1m\rDirectory fully cleaned ${TRASH} ${TRASH} ${TRASH}          \033[0m"

re: 
	@echo "\033[32;1m\rMinishell recompiling ${RE}          \033[0m"
	@make -s fclean 
	@make -s all
	

re_minishell: fclean_minishell $(NAME)

re_libft:
	@make -s -C libft re

bonus: all

.PHONY: all clean fclean re libft clean_minishell clean_libft fclean_minishell fclean_libft re_minishell re_libft
