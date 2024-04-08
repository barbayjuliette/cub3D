# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:11:22 by jbarbay           #+#    #+#              #
#    Updated: 2024/04/08 12:11:48 by jbarbay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/arg_validation.c \
		srcs/cub3D.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = cub3D
OBJS = ${SRCS:.c=.o}
LIBFT = ./libft
LFLAGS = -L${LIBFT} -lft
all: ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) runlibft
	$(CC) $(OBJS) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -o $(NAME)

runlibft:
	@make all -C libft

clean:
		${RM} ${OBJS}
		@make fclean -C libft

fclean: clean
		${RM} ${NAME} ${OBJS}

re: fclean all

.PHONY: all clean fclean re
