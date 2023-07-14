# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 19:28:25 by samusanc          #+#    #+#              #
#    Updated: 2023/07/14 07:27:41 by samusanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror -I ./ -I ./libft/
CC		= gcc $(CFLAGS)
LIBFT	= -L./libft/ -lft
MAIN	= ./main.c
SRCS	= $(MAIN) \
		  ./ft_error_log.c \
		  ./ft_free_utils.c \
		  ./ft_pipex_utils.c \
		  ./ft_childs.c

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

clean:
	@make -sC ./libft/ clean
	@rm -f $(OBJS)

.PHONY: all
