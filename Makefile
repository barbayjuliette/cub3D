# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:11:22 by jbarbay           #+#    #+#              #
#    Updated: 2024/04/25 14:54:21 by jbarbay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAC
# NAME = cub3D
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g
# MLX = mlxopengl
# LIBFT = ./libft
# LFLAGS = -L${LIBFT} -lft
# LXFLAGS = -lmlx -framework OpenGL -framework AppKit
# HEADER = cub3d.h

# SRC = cub3D \
# 		parsing/validation_helpers \
# 		parsing/colors_validation \
# 		parsing/map_validation \
# 		parsing/get_arguments \
# 		parsing/utils \
# 		parsing/quoted_path \
# 		raycasting/raycasting \
# 		raycasting/draw \
# 		raycasting/calculations

# FIL = $(addsuffix .c, $(addprefix srcs/, $(SRC)))
# LEAKS = -L/usr/local -llsan
# OBJ = $(FIL:.c=.o)

# BIN = $(addsuffix .o, $(SRC))

# .PHONY: all clean fclean re bonus

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@make all -C libft
# 	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) -L./libft -lft $(OBJ)
# 	@echo "Everything compiled"

# clean:
# 	rm -rf $(OBJ) $(B_OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# bonus: fclean $(B_OBJ)
# 	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(B_OBJ)

# 	./$(NAME)


# .SILENT: all clean fclean

# LINUX
SRCS =  srcs/cub3D.c \
		srcs/parsing/validation_helpers.c \
		srcs/parsing/colors_validation.c \
		srcs/parsing/map_validation.c \
		srcs/parsing/get_arguments.c \
		srcs/parsing/utils.c \
		srcs/parsing/quoted_path.c \
		srcs/raycasting/raycasting.c \
		srcs/raycasting/draw.c \
		srcs/raycasting/calculations.c \
		srcs/end_cub.c \

CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = cub3D
OBJS = ${SRCS:.c=.o}
LIBFT = ./libft
LFLAGS = -L${LIBFT} -lft
all: ${NAME}

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) runlibft
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -o $(NAME)
	@echo "Everything compiled"

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
