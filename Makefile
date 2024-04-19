# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:11:22 by jbarbay           #+#    #+#              #
#    Updated: 2024/04/19 11:30:34 by jbarbay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  srcs/cub3D.c \
		srcs/parsing/validation_helpers.c \
		srcs/parsing/colors_validation.c \
		srcs/parsing/map_validation.c \
		srcs/parsing/get_arguments.c \
		srcs/parsing/utils.c \
		srcs/parsing/quoted_path.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = cub3D
OBJS = ${SRCS:.c=.o}
LIBFT = ./libft
LFLAGS = -L${LIBFT} -lft
all: ${NAME}

# $(NAME):
# 		@make all bonus -C libft
# 		$(CC) $(SRCS) -L./libft -lft -o ${NAME}

# %.o: %.c
# 	${CC} -c $<

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) runlibft
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -o $(NAME)

runlibft:
	@make all -C libft

clean:
		${RM} ${OBJS}
		@make fclean -C libft

fclean: clean
		${RM} ${NAME} ${OBJS}

re: fclean all

.PHONY: all clean fclean re

.SILENT: all clean fclean
