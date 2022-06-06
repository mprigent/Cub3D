NAME =		cub3d

CC =		gcc

CFLAGS =	#-Wall -Wextra -Werror

SAN =		-fsanitize=address -g

LIB =		-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

SRC =		main.c \
			utils.c \
			events.c \
			parsing.c \
			parsing2.c \
			str_utils.c \
			strs_utils.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_memcpy.c \
			ft_strlcat.c \
			ft_strncmp.c \
			ft_putnbr_fd.c

OBJ =		${SRC:.c=.o}

all:		${NAME}

${NAME}:	${OBJ}
			${CC} ${FLAGS} ${SAN} ${LIB} -o ${NAME} ${OBJ}

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY :	all clean fclean re