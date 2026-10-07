CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -Iinclude
HEADER = include/philo.h
NAME = philo
SRC = 	src/philo.c \
	src/data.c \
	src/data_utils.c \
	src/routine.c \
	src/routine_utils.c \
	src/rules.c \
	src/observer.c \
	src/utils.c
OBJ = $(SRC:.c=.o)

BONUS = philo_bonus
BONUS_SRC = bonus/philo_bonus.c \
	    bonus/utils_bonus.c \
	    bonus/data_bonus.c \
	    bonus/rules_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJ) -lpthread

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re:	fclean all

.PHONY: all clean fclean re
