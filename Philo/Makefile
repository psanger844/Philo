NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -o3
SRCS = main.c philo.c helper_funktions.c init_structs.c time.c routine.c free_funktions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
