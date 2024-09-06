# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 14:40:03 by jhouyet           #+#    #+#              #
#    Updated: 2024/03/27 14:36:57 by lvitale          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m 

NAME		= minishell

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= include/

SRC 		= 	$(SRC_DIR)main.c \
				$(SRC_DIR)loop.c \
				$(SRC_DIR)signals.c \
				$(SRC_DIR)print.c \
				$(SRC_DIR)lexer/lexer.c \
				$(SRC_DIR)lexer/handle.c \
				$(SRC_DIR)lexer/quotes.c \
				$(SRC_DIR)lexer/tokens.c \
				$(SRC_DIR)lexer/utils.c \
				$(SRC_DIR)parser/parser.c \
				$(SRC_DIR)parser/handle.c \
				$(SRC_DIR)executor/executor.c \
				$(SRC_DIR)executor/commands.c \
				$(SRC_DIR)executor/heredocs.c \
				$(SRC_DIR)executor/heredocs_utils.c \
				$(SRC_DIR)executor/pipes.c \
				$(SRC_DIR)executor/redirections.c \
				$(SRC_DIR)executor/simple.c \
				$(SRC_DIR)exit/errors.c \
				$(SRC_DIR)exit/exit.c \
				$(SRC_DIR)exit/free.c \
				$(SRC_DIR)exit/free_2.c \
				$(SRC_DIR)expander/expandeur.c \
				$(SRC_DIR)expander/expandeur_check.c \
				$(SRC_DIR)expander/expandeur_get.c \
				$(SRC_DIR)expander/expandeur_utils.c \
				$(SRC_DIR)builtins/cd.c \
				$(SRC_DIR)builtins/echo.c \
				$(SRC_DIR)builtins/env.c \
				$(SRC_DIR)builtins/exit.c \
				$(SRC_DIR)builtins/export.c \
				$(SRC_DIR)builtins/pwd.c \
				$(SRC_DIR)builtins/unset.c \
				$(SRC_DIR)builtins/builtins_utils.c \

OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT 		= libft/lib/libft.a
LIBFT_PATH 	= libft/

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
	
CC			= gcc -ggdb3
RM			= rm -f
C_FLAGS		= -Wall -Wextra -Werror
LDFLAGS 	= -lreadline -lhistory
INCS 		= -I$(INC_DIR) -I. -I$(READLINE_DIR)/include

TOTAL_FILES 	:= $(words $(SRC))
CURRENT_FILE 	:= 0

define progress_bar_minishell
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "\r$(YELLOW)Compiling Minishell... [%-$(TOTAL_FILES)s] %d/%d $(NC)" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	$(call progress_bar_minishell)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Linking objects to create executable...$(NC)"
	@$(CC) $(OBJ) -L$(LIBFT_PATH)lib -lft -o $(NAME) $(READLINE_LIB)
	@echo "$(BLUE)Executable $(NAME) created!$(NC)"

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(NC)"
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@echo "$(ORANGE)Cleaning objects for Libft...$(NC)"
	@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null
	@echo "$(GREEN)Cleaned objects Libft!$(NC)"
	@echo "$(ORANGE)Cleaning objects for Minishell...$(NC)"
	@$(RM) $(OBJ_DIR)*.o
	@echo "$(GREEN)Cleaned Minishell objects!$(NC)"

fclean: clean
	@echo "$(ORANGE)Fully cleaning library for Libft...$(NC)"
	@$(MAKE) fclean -C $(LIBFT_PATH) > /dev/null
	@echo "$(BLUE)Fully cleaned Libft!$(NC)"
	@echo "$(ORANGE)Fully cleaning library for Minishell...$(NC)"
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(BLUE)Fully cleaned Minishell!$(NC)"

re: fclean all

.PHONY: all clean fclean re