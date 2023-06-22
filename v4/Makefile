NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address
SRCS	=	srcs/main.c \
			srcs/info.c \
			srcs/operation.c \
			srcs/philos.c \
			srcs/err.c \
			srcs/ft_isdigit.c \
			srcs/ft_atoi.c \
			srcs/ft_strlen.c \
			srcs/free.c
OBJS	=	${SRCS:.c=.o}
all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
re: fclean all
