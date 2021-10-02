OBJS    =       ${SRCS:.c=.o}

SRCS	=	srcs/ft_init.c srcs/ft_philosophers.c srcs/ft_utils.c srcs/ft_algo.c

CC      =       clang

FLAGS   =       -Wall -Wextra -Werror

NAME    =       philo

RM      =       rm -rf

LINK	=		-pthread

all:    ${NAME}

.c.o:
	${CC} ${FLAGS} -c -g $< -o ${<:.c=.o}

${NAME}:        ${OBJS}
		${CC} -o ${NAME} ${LINK} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:         clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re