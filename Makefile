# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tytang <tytang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 12:24:33 by tytang            #+#    #+#              #
#    Updated: 2023/12/19 15:36:11 by tytang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f
LINKS = -I./includes -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework Appkit

SRCS_DIR = sources/
FILES = events \
        main \
        parse_scene \
		vector_calculations \
		sphere \
		blue_to_white \
		sphere2 \
		debug_and_print \
		
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

all: mlx_library $(NAME)
	./minirt

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
