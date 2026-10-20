CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -Iinclude
HEADER = include/philo.h
BONUS_HEADER = include/bonus.h
NAME = philo
SRC = 	src/philo.c \
	src/data.c \
	src/data_utils.c \
	src/routine.c \
	src/routine_utils.c \
	src/rules.c \
	src/observer.c \
	src/utils.c \
	src/time.c
OBJ = $(SRC:.c=.o)

BONUS = philo_bonus
BONUS_SRC = bonus/philo_bonus.c \
	    bonus/utils_bonus.c \
	    bonus/data_bonus.c \
	    bonus/rules_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS) 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

$(BONUS): $(BONUS_OBJ)
	$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJ) -lpthread

src/%.o: src/%.c $(HEADER) 
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

bonus/%.o: bonus/%.c $(BONUS_HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re:	fclean all

.PHONY: all bonus clean fclean re
