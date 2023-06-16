NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror 
#-pthread -g -fsanitize=thread

OBJ = $(SRC:.c=.o)

SRC = philo.c help.c

all : $(NAME)

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all