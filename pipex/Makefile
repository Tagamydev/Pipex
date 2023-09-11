# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 19:28:25 by samusanc          #+#    #+#              #
#    Updated: 2023/09/11 13:06:21 by samusanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror -I ./ -I ./libft/
CC		= gcc $(CFLAGS)
LIBFT	= -L./libft/ -lft
UTILS	= pipex_utils_
MAIN	= ./main.c
SRCS	= $(MAIN) \
		  $(UTILS)error_handling.c \
		  $(UTILS)get_path.c \
		  $(UTILS)child_utils.c \
		  $(UTILS)childs.c \

O_DIR	= ./objects/
OBJS	= $(addprefix $(O_DIR)/, $(SRCS:.c=.o))

$(O_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $(O_DIR)/$(<:.c=.o)

all: $(NAME) $(SRCS)

$(NAME): $(OBJS)
	@make -sC ./libft/
	@$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

re: fclean all

fclean: clean
	@make -sC ./libft/ fclean
	@rm -f $(NAME)
	@rm -rf objects

clean:
	@make -sC ./libft/ clean
	@rm -f $(OBJS)

.PHONY: all
