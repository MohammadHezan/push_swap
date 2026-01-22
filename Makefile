NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -I srcs

SRCS = srcs/main.c \
       srcs/parse.c \
       srcs/split.c \
       srcs/utils.c \
       algo/push.c \
       algo/sort.c \
       algo/sort_small.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c srcs/push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
