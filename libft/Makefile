SRCS = ft_atoi.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memmove.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_itoa.c \
		ft_substr.c \
		ft_putnbr_fd.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_printf/ft_printf.c \
		ft_printf/helpers.c \
		ft_printf/library.c \
		ft_printf/conversions.c

BONUS_SRCS = 	ft_lstadd_back_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = libft.a
OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
		${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
		${RM} ${NAME} $(BONUS_OBJS)

re: fclean all

bonus: ${BONUS_OBJS}
		$(CC) $(CFLAGS) -c $(BONUS_SRCS)
		ar rcs $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean re
