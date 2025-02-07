NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c utils.c
OBJ = $(SRC:.c=.o)
HEADER = pipex.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) libft.a -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

