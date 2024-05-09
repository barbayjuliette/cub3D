# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:11:22 by jbarbay           #+#    #+#              #
#    Updated: 2024/05/09 15:41:04 by jbarbay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# LINUX
SRCS =	srcs/parsing/validation_helpers.c \
		srcs/parsing/colors_validation.c \
		srcs/parsing/map_validation.c \
		srcs/parsing/get_arguments.c \
		srcs/parsing/utils.c \
		srcs/parsing/quoted_path.c \
		srcs/raycasting/raycasting.c \
		srcs/raycasting/raycasting_helpers.c \
		srcs/raycasting/draw.c \
		srcs/raycasting/calculations.c \
		srcs/actions/rerender.c \
		srcs/actions/movement.c \
		srcs/actions/rotate.c \
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
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) runlibft
	$(CC) $(OBJS) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -o $(NAME)
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

# **************************************************************************** #

# MAC
# NAME = cub3D
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g
# MLX = mlxopengl
# RM = rm -rf
# LIBFT = ./libft
# LFLAGS = -L${LIBFT} -lft
# LXFLAGS = -lmlx -framework OpenGL -framework AppKit
# HEADER = cub3d.h

# SRCS =  srcs/cub3D.c \
# 		srcs/parsing/validation_helpers.c \
# 		srcs/parsing/colors_validation.c \
# 		srcs/parsing/map_validation.c \
# 		srcs/parsing/get_arguments.c \
# 		srcs/parsing/utils.c \
# 		srcs/parsing/quoted_path.c \
# 		srcs/raycasting/raycasting.c \
# 		srcs/raycasting/raycasting_helpers.c \
# 		srcs/raycasting/draw.c \
# 		srcs/raycasting/calculations.c \
# 		srcs/actions/rerender.c \
# 		srcs/actions/movement.c \
# 		srcs/actions/rotate.c \
# 		srcs/end_cub.c \

# OBJS = ${SRCS:.c=.o}

# .PHONY: all clean fclean re bonus

# all: $(NAME)

# $(NAME): $(OBJS)
# 	@make all -C libft
# 	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) -L./libft -lft $(OBJS)
# 	@echo "Everything compiled"

# clean:
# 		${RM} ${OBJS}
# 		@make fclean -C libft

# fclean: clean
# 		${RM} ${NAME} ${OBJS}

# re: fclean all

# .PHONY: all clean fclean re

# .SILENT: all clean fclean
