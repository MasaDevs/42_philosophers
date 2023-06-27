NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror 
INCLUDE	=	-I ./includes
SRCS	=	srcs/main.c \
			srcs/info.c \
			srcs/print.c \
			srcs/operation.c \
			srcs/philos.c \
			srcs/ft_atoi.c \
			srcs/ft_isdigit.c \
			srcs/ft_strlen.c \
			srcs/err.c \
			srcs/free.c

OBJDIR	=	obj
OBJS	=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))


all: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLXLIB) $(LIBDIR) $(LIB) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -f $(NAME)
re:	fclean all

.PHONY:
	all clean fclean re

