# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tytang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 12:24:33 by tytang            #+#    #+#              #
#    Updated: 2022/11/24 13:42:10 by tytang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
FLAGS = -Wall -Wextra -g
RM = rm -f
LINKS = -I./includes -L./libft -lft -L./mlx_linux -lmlx_Linux -L/usr/lib -lX11 -lXext -lXrandr -lXinerama -lXcursor -lm -lGL -lz

SRCS_DIR = sources/

FILES = main \
		math \
		sphere \
		plane	\
		cylinder \

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

all: configure_mlx $(NAME)

# Run the configure script for MLX before compiling the project
configure_mlx:
	@$(MAKE) re -C ./libft
	@$(MAKE) -C ./mlx_linux
	@cd mlx_linux && ./configure

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS)

# Updated object file rule to include correct include paths and compilation flags
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./mlx_linux clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: re fclean clean all configure_mlx
