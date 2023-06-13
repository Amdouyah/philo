NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = philo.c help.c

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

fclean : clean

re : fclean all