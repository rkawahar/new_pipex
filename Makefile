SRCS = 	ft_print_specifier.c ft_printf.c ft_split.c here_doc.c list.c main.c path.c \
path2.c pipex_utils.c 
NAME = pipex
CC = cc
CFLGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)

%.o : %.c
	$(CC) $(CFLGS) -c $^ -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 