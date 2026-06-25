CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDE = -Iinclude
HEADER = include/philo.h
NAME = philo
SRC =	src/philo.c \
		src/data.c \
		src/routine.c \
		src/rules.c \
		src/observer.c \
		src/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
