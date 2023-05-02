NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
SRCS	=	srcs/main.c \
			srcs/info.c \
			srcs/operation.c \
			srcs/philos.c
OBJS	=	${SRCS:.c=.o}
all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME}	${OBJS}
clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
re: fclean all
