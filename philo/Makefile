NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c init.c observer.c parser.c routine.c routine_actions.c utils.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
