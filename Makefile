# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/22 17:06:17 by snakajim          #+#    #+#              #
#    Updated: 2024/12/22 17:45:42 by snakajim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT = libft/libft.a

MAND_SRC = main.c \
		   pipex.c \
		   utils.c \
		   error.c \
		   free.c \
		   parse.c \
		   child.c
BONUS_SRC = main_bonus.c \
			pipex.c \
			utils.c \
			error.c \
			free.c \
			parse.c \
			child.c
OBJ_DIR = obj/
MAND_OBJS = $(addprefix $(OBJ_DIR), $(MAND_SRC:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR), $(BONUS_SRC:.c=.o))

all : $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(OBJ_DIR)%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@ 

$(NAME): $(LIBFT) $(MAND_OBJS)
	$(CC) $(CFLAGS) $(MAND_OBJS) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	@make -sC libft

clean:
	@$(RM) $(OBJ_DIR)
	@make -sC libft clean

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@make -sC libft fclean

re : fclean all

.PHONY: all clean fclean re bonus