NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = philo.c ft_atoi.c

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

fclean : clean

re : fclean all