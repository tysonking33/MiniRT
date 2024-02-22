# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tytang <tytang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 12:24:33 by tytang            #+#    #+#              #
#    Updated: 2024/02/22 17:13:41 by tytang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f
LINKS = -I./includes -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework Appkit

SRCS_DIR = sources/
FILES = main \
		player \
		events \
		map \
		
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

all: mlx_library $(NAME)
	./cub3d

$(NAME): $(OBJS)
	@$(MAKE) re -C ./libft
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS)

mlx_library:
	@$(MAKE) -C ./mlx

$(OBJS): %.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./mlx clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re mlx_library
