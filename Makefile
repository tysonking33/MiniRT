# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tytang <tytang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 12:24:33 by tytang            #+#    #+#              #
#    Updated: 2023/12/04 17:51:40 by tytang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f
LINKS = -I./includes -L./libft -lft -L./mlx -lmlx -framework OpenGL \
	   	-framework Appkit

SRCS_DIR = sources/

FILES = events \
        main \
        parse_scene \
		vec3_deviants \
		vec3 \

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	clear
	./minirt

$(NAME) : $(OBJS)
	@$(MAKE) re -C ./libft
	@$(MAKE) -C ./mlx
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS)

$(OBJS): %.o : %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./mlx clean

fclean:	clean
	rm -f $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: re fclean clean
