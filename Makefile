# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 13:48:39 by pdeson            #+#    #+#              #
#    Updated: 2024/10/16 15:26:49 by pdeson           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= miniRT
PRINT_PREFIX    =	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m\
                   		 $(NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m
CC 				= @cc
CFLAGS 			= -Werror -Wall -Wextra -g3 -Ofast
SRC_DIR			= srces/
OBJ_DIR			= .objs/

UNAME			= $(shell uname -s)
NUMPROC			= 8

ifeq ($(UNAME), Linux)
	NUMPROC 	= $(shell grep -c ^processor /proc/cpuinfo)
endif

CFLAGS			+= -D THREADS=$(NUMPROC)


LIBFT_LIB 		= libft/libft.a 
LIBMLX			= MLX42

HEADERS			= -I $(LIBMLX)/Iinclude
LIBS			= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Recherche de tous les fichiers .c dans les sous-répertoires de srces/
SRCES			= $(shell find $(SRC_DIR) -name "*.c")
# Remplacement des extensions .c par .o et déplacement dans le répertoire OBJ_DIR
OBJS			= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCES))

NUM_FILES		=	$(words $(SRCES))
BAR_LENGTH		=	$(shell echo "$$(($(NUM_FILES)*1))")

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 > /dev/null

# Création des sous-répertoires nécessaires dans OBJ_DIR
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(HEADERS)

$(NAME): $(OBJS)
	@printf "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m["
	@for i in $(shell seq 1 $(BAR_LENGTH)); do \
		sleep 0.01; \
		printf "\033[38;5;40m▲▼"; \
	done
	@printf "\033[38;5;40m] \033[0m\n"
	@make -C libft/ all --no-print-directory
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo "$(PRINT_PREFIX)\033[0;32m Done \033[0;37m\n"

clean:
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@make -C libft/ clean --no-print-directory
	@rm -rf $(OBJS) $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(PRINT_PREFIX)\033[0;32m Done \033[0;37m\n"
	
fclean: clean
	@make -C libft/ fclean --no-print-directory
	@rm -rf $(NAME) $(OBJ_DIR)

re: fclean all

run: all clean
	./$(NAME)

.PHONY: all clean fclean re run libmlx