# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 14:49:33 by mprigent          #+#    #+#              #
#    Updated: 2022/06/08 14:49:36 by mprigent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3d

SRCS	=	${shell find ./srcs -name "*.c"}

OBJS	=	${SRCS:.c=.o}
CC		=	clang
FLAGS	=	-Wall -Werror -Wextra -fsanitize=address -g3
SYSTEM = $(shell uname)

ifeq (${SYSTEM}, Darwin)
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m
endif

ifeq (${SYSTEM}, Linux)
_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= $'\033[37m
endif

ifeq (${SYSTEM}, Darwin)
INCS = -I ./includes -I ./mlx
LIBC = -L ./mlx -lmlx
MLX_FLAGS = -Ofast -framework OpenGL -framework AppKit
MLX_USED = mlx
endif

ifeq (${SYSTEM}, Linux)
INCS = -I ./includes -I ./mlx
LIBC = ./mlx/libmlx.a
MLX_FLAGS	=	-L./mlx -lmlx -lX11 -lbsd -lXext -lm
MLX_USED = mlx
endif

all:		${NAME}

.c.o:
			@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"
			@${CC} ${FLAGS} -Ofast ${INCS} -c $< -o $@

${NAME}:	${OBJS}
			@printf "%-15s ${_CYAN}${_BOLD}${MLX_USED}${_END}...\n" "Compiling"
			@${MAKE} -C ${MLX_USED} >/dev/null 2>&1
			@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
			@${CC} ${FLAGS} ${INCS} ${MLX_FLAGS} -o ${NAME} ${OBJS} ${LIBC}
			@printf "\n${_GREEN}${_BOLD}Compilation done !${_END}\n"

clean:		
			@printf "%-15s ${_RED}${_BOLD}mlx binary files${_END}...\n" "Deleting"
			@${MAKE} -C ${MLX_USED} clean >/dev/null
			@printf "%-15s ${_RED}${_BOLD}${NAME} binary files${_END}...\n" "Deleting"
			@rm -f ${OBJS} ${OBJS_BONUS}


fclean:		clean
			@printf "%-15s ${_RED}${_BOLD}${NAME}${_END}...\n" "Deleting"
			@rm -f ${NAME}

re:			fclean all

.PHONY:		all fclean clean all bonus